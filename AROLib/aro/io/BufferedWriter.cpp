#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/BufferedWriter.h>

namespace aro {

namespace io {

vint BufferedWriter::defaultCharBufferSize = 8192;

BufferedWriter::BufferedWriter(RWriter out)
   :Writer(out)
{
   cb = new Array<vchar>(defaultCharBufferSize);
   nChars = defaultCharBufferSize;
   lineSeparator = "\n";
   thisref->out = out;
   nextChar = 0;
}


BufferedWriter::BufferedWriter(RWriter out, vint size)
   :Writer(out)
{
   if(size < 0 )
      ex_throw new ArgumentException("Buffer size <= 0");

   cb = new Array<vchar>(size);
   lineSeparator = "\n";
   thisref->out = out;
   nChars = size;
   nextChar = 0;
}

void BufferedWriter::ensureOpen()
{
   if(out == nullref)
      ex_throw new IOException("stream cloased");
}

void BufferedWriter::flushBuffer()
{
   sync_lock(lock)
   {
      ensureOpen();

      if(nextChar == 0)
         return;

      out->write(cb, 0, nextChar);
      nextChar = 0;
   }
}

void BufferedWriter::write(vint c)
{
   sync_lock(lock)
   {
      ensureOpen();

      if(nextChar >= nChars)
         flushBuffer();

      cb[nextChar++] = (vchar) c;
   }
}

void BufferedWriter::write(RArray<vchar> cbuf, vint off, vint num)
{
   sync_lock(lock)
   {
      ensureOpen();

      if((off < 0) || (off > cbuf->length) || (num < 0) ||
        ((off + num) > cbuf->length) || ((off + num) < 0))
         ex_throw new IndexException();
      
      else if (num == 0)
         return;

      if(num >= nChars)
      {
		   /* If the request length exceeds the size of the output buffer,
		      flush the buffer and then write the data directly.  In this
		      way buffered streams will cascade harmlessly. */
         flushBuffer();
         out->write(cbuf, off, num);
         return;
      }

      vint b = off, t = off + num;
      while(b < t)
      {
         vint d = min(nChars - nextChar, t - b);
         cb->copy(nextChar, cbuf, b, d);
         b += d;
         nextChar += d;

         if(nextChar >= nChars)
            flushBuffer();
      }
   }
}

void BufferedWriter::write(RString s, vint off, vint num)
{
   sync_lock(lock)
   {
      ensureOpen();

      vint b = off, t = off + num;
      while(b < t)
      {
         vint d = min(nChars - nextChar, t - b);
         s->getChars(b, b + d, cb, nextChar);
         b += d;
         nextChar += d;

         if(nextChar >= nChars)
            flushBuffer();
      }
   }
}

void BufferedWriter::newLine()
{
   Writer::write(lineSeparator);
}

void BufferedWriter::flush()
{
   sync_lock(lock)
   {
      flushBuffer();

      out->flush();
   }
}

void BufferedWriter::close()
{
   sync_lock(lock)
   {
      if(out == nullref)
         return;

      ex_try
      {
         flushBuffer();

         out->close();
         out = nullref;
         cb = nullref;
      }
      ex_catch
      {
         ex_handle(Exception)
         {
            out->close();
            out = nullref;
            cb = nullref;

            ex_rethrow;
         }
      }
      ex_end
   }
}

} /* namespace io */

} /* namespace aro */
