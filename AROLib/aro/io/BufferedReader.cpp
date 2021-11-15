#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/BufferedReader.hpp>

namespace aro {

namespace io {

const vint BufferedReader::UNMARKED = -1;
const vint BufferedReader::INVALIDATED = -2;

vint BufferedReader::defaultCharBufferSize = 8192;
vint BufferedReader::defaultExpectedLineLength = 80;

BufferedReader::BufferedReader(RReader in)
   :Reader(in)
{
   skipLF = false;
   readAheadLimit = 0;
   markedSkipLF = false;
   markedChar = UNMARKED;

   thisref->in = in;
   nextChar = nChars = 0;
   cb = new Array<vchar>(defaultCharBufferSize);
}

BufferedReader::BufferedReader(RReader in, vint size)
   :Reader(in)
{
   if(size <= 0)
      ex_throw new ArgumentException("Buffer size <= 0");

   skipLF = false;
   readAheadLimit = 0;
   markedSkipLF = false;
   markedChar = UNMARKED;

   thisref->in = in;
   nextChar = nChars = 0;
   cb = new Array<vchar>(size);
}

void BufferedReader::ensureOpen()
{
   if(in == nullref)
      ex_throw new IOException("stream closed");
}

void BufferedReader::fill()
{
   vint dst;

   if(markedChar <= UNMARKED)
      dst = 0; // no mark
   else
   {
      vint delta = nextChar - markedChar;
      if(delta >= readAheadLimit)
      {
         /* Gone past read-ahead limit: Invalidate mark */
         markedChar = INVALIDATED;
         readAheadLimit = 0;
         dst = 0;
      }
      else
      {
         if(readAheadLimit <= cb->length)
         {
            /* Shuffle in the current buffer */
            cb->copy(0, cb, markedChar, delta);
            markedChar = 0;
            dst = delta;
         }
         else
         {
            /* Reallocate buffer to accommodate read-ahead limit */
            RArray<vchar> ncb = new Array<vchar>(readAheadLimit);
            ncb->copy(0, cb, markedChar, delta);
            cb = ncb;
            markedChar = 0;
            dst = delta;
         }

         nextChar = nChars = delta;
      }
   }

   vint n;

   do{
      n = in->read(cb, dst, cb->length - dst);
   }while(n == 0);

   if(n > 0)
   {
      nChars = dst + n;
      nextChar = dst;
   }
}

vint BufferedReader::read()
{
   sync_lock(lock)
   {
      ensureOpen();

      for(;;)
      {
         if(nextChar >= nChars)
         {
            fill();
            if(nextChar >= nChars)
               return -1;
         }

         if(skipLF)
         {
            skipLF = false;
            if(cb[nextChar] == '\n')
            {
               nextChar++;
               continue;
            }
         }

         return cb[nextChar++];
      }
   }
}

vint BufferedReader::read1(RArray<vchar> cbuf, vint off, vint len)
{
   if(nextChar >= nChars)
   {
	    /* If the requested length is at least as large as the buffer, and
	       if there is no mark/reset activity, and if line feeds are not
	       being skipped, do not bother to copy the characters into the
	       local buffer.  In thisref way buffered streams will cascade
	       harmlessly. */
      if(len >= cb->length && markedChar <= UNMARKED && !skipLF)
         return in->read(cbuf, off, len);

      fill();
   }

   if(nextChar >= nChars)
      return -1;

   if(skipLF)
   {
      skipLF = false;

      if(cb[nextChar] == '\n')
      {
         nextChar++;
         if(nextChar >= nChars)
            fill();
         if(nextChar >= nChars)
            return -1;
      }
   }

   vint n = Math::minimum(len, nChars - nextChar);
   cbuf->copy(off, cb, nextChar, n);
   nextChar += n;
   return n;
}

vint BufferedReader::read(RArray<vchar> cbuf, vint off, vint len)
{
   sync_lock(lock)
   {
      ensureOpen();

      if((off < 0) || (off > cbuf->length) || (len < 0) ||
         ((off + len) > cbuf->length) || ((off + len) < 0))
         ex_throw new IndexException();

      else if(len == 0)
         return 0;

      vint n = read1(cbuf, off, len);

      if(n <= 0)
         return n;

      while((n < len) && in->ready())
      {
         vint n1 = read1(cbuf, off + n, len - n);
         if(n1 <= 0)
            break;
         n += n1;
      }

      return n;
   }
}

RString BufferedReader::readLine(vbool ignoreLF)
{
   vint startChar;
   RStringBuffer s = nullref;

   sync_lock(lock)
   {
      ensureOpen();

      vbool omitLF = ignoreLF || skipLF;

      //bufferLoop:
      for(;;)
      {
         if(nextChar >= nChars)
            fill();

         if(nextChar >= nChars) // EOF
         {
            if(s != nullref && s->length() > 0)
               return s->toString();
            else
               return nullref;
         }

         vbool eol = false;
         vchar c = 0;
         vint i;

         /* Skip a leftover '\n', if necessary */
         if(omitLF && (cb[nextChar] == '\n'))
            nextChar++;

         skipLF = false;
         omitLF = false;

         //charLoop:
         for(i = nextChar; i < nChars; i++)
         {
            c = cb[i];
            if ((c == '\n') || (c == '\r'))
            {
               eol = true;
               break; //charLoop;
            }
         }

         startChar = nextChar;
         nextChar = i;

         if(eol)
         {
            RString str;
            if(s == nullref)
               str = new String(cb, startChar, i - startChar);
            else
            {
               s->append(cb, startChar, i - startChar);
               str = s->toString();
            }

            nextChar++;

            if(c == '\r')
               skipLF = true;

            return str;
         }

         if (s == nullref)
            s = new StringBuffer(defaultExpectedLineLength);

         s->append(cb, startChar, i - startChar);
      }
   }
}

RString BufferedReader::readLine()
{
   return readLine(false);
}

vlong BufferedReader::skip(vlong n)
{
   if(n < 0L)
      ex_throw new ArgumentException("skip value is negative");

   sync_lock(lock)
   {
      ensureOpen();

      vlong r = n;
      while(r > 0)
      {
         if(nextChar >= nChars)
            fill();

         if(nextChar >= nChars)	// EOF
            break;

         if(skipLF)
         {
            skipLF = false;

            if(cb[nextChar] == '\n')
               nextChar++;
         }

         vlong d = nChars - nextChar;

         if(r <= d)
         {
            nextChar += r;
            r = 0;
            break;
         }
         else
         {
            r -= d;
            nextChar = nChars;
         }
      }

      return n - r;
   }
}

vbool BufferedReader::ready()
{
   sync_lock(lock)
   {
      ensureOpen();

      /* If newline needs to be skipped and the next vchar to be read
	    * is a newline character, then just skip it right away. */
      if(skipLF)
      {
         if (nextChar >= nChars && in->ready())
            fill();

         if(nextChar < nChars)
         {
            if(cb[nextChar] == '\n')
               nextChar++;

            skipLF = false;
         }
      }

      return (nextChar < nChars) || in->ready();
   }
}

vbool BufferedReader::markSupported()
{
   return true;
}

void BufferedReader::mark(vint readAheadLimit)
{
   if(readAheadLimit < 0)
      ex_throw new ArgumentException("Read-ahead limit < 0");

   sync_lock(lock)
   {
      ensureOpen();

      thisref->readAheadLimit = readAheadLimit;
      markedSkipLF = skipLF;
      markedChar = nextChar;
   }
}

void BufferedReader::reset()
{
   sync_lock(lock)
   {
      ensureOpen();

      if(markedChar < 0)
         ex_throw new IOException((markedChar == INVALIDATED) ?
                                    "Mark invalid" : "Stream not marked");

      nextChar = markedChar;
      skipLF = markedSkipLF;
   }
}

void BufferedReader::close()
{
   sync_lock(lock)
   {
      if(in == nullref)
         return;

      in->close();
      in = nullref;
      cb = nullref;
   }
}

} /* namespace io */

} /* namespace aro */
