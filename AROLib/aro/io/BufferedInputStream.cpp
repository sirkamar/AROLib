#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/BufferedInputStream.hpp>

namespace aro {

namespace io {

const vint BufferedInputStream::defaultBufSize = 8192;

BufferedInputStream::BufferedInputStream(RInputStream is)
   :FilterInputStream(is)
{
   markpos = -1;
   count = pos = marklimit = 0;
   buf = new Array<vint>(defaultBufSize);
}

BufferedInputStream::BufferedInputStream(RInputStream is, vint size)
   :FilterInputStream(is)
{
   if(size <= 0)
      ex_throw new ArgumentException("Buffer size <= 0");
   
   markpos = -1;
   buf = new Array<vint>(size);
   count = pos = marklimit = 0;
}

void BufferedInputStream::fill()
{
   RArray<vint> buffer = getBufIfOpen();
   
   if(markpos < 0)
      pos = 0;    //no mark: throw away the buffer
   else if(pos >= buffer->length)   //no room left in buffer
   {
      if(markpos > 0)   //can throw away early part of the buffer
      {
         vint sz = pos-markpos;
         buffer->copy(0, buffer, markpos, sz);
         pos = sz;
         markpos = 0;
      }
      else if(buffer->length >= marklimit)
      {
         markpos = -1;  //buffer got too big, invalidate mark
         pos = 0;       //drop buffer contents
      }
      else     //grow buffer
      {
         vint nsz = pos * 2;
         if(nsz > marklimit)
            nsz = marklimit;
         RArray<vint> nbuf = new Array<vint>(nsz);
         nbuf->copy(0, buffer, 0, pos);
         
         if(buf == nullref)
            ex_throw new IOException("Stream closed");
         
         buffer = buf = nbuf;
      }
   }
   
   count = pos;
   
   vint n = getInIfOpen()->read(buffer, pos, buffer->length - pos);
   
   if(n > 0)
      count = n + pos;
}

RArray<vint> BufferedInputStream::getBufIfOpen()
{
   RArray<vint> buffer = buf;
   
   if(buffer == nullref)
      ex_throw new IOException("Stream closed");
   
   return buffer;
}

RInputStream BufferedInputStream::getInIfOpen()
{
   RInputStream input = in;
   
   if(input == nullref)
      ex_throw new IOException("Stream closed");
   
   return input;
}

vint BufferedInputStream::read()
{
   if(pos >= count)
   {
      fill();
      if(pos >= count)
         return -1;
   }
   
   return getBufIfOpen()[pos++] & 0xff;
}

vint BufferedInputStream::read(RArray<vint> bytes)
{
   return read(bytes, 0, bytes->length);
}

vint BufferedInputStream::read(RArray<vint> bytes, vint off, vint num)
{
   getBufIfOpen(); // Check for closed stream
   if((off | num | (off + num) | (bytes->length - (off + num))) < 0)
      ex_throw new IndexException();
   
   else if(num == 0)
      return 0;
   
   vint n=0;
   while(true)
   {
      vint nread = read1(bytes, off + n, num - n);
      if(nread <= 0)
         return (n == 0) ? nread : n;
      
      n += nread;
      if(n >= num)
         return n;
      
      //if not closed but no bytes available, return
      RInputStream input = in;
      if(input != nullref && input->available() <= 0)
         return n;
   }
   
   return n;
}

vint BufferedInputStream::read1(RArray<vint> bytes, vint off, vint num)
{
   vint avail = count - pos;
   
   if(avail <= 0)
   {
      //If the requested length is at least as large as the buffer, and
      //if there is no mark/reset activity, do not bother to copy the
      //bytes into the local buffer. In this way buffered streams will
      //cascade harmlessly.
      if(num >= getBufIfOpen()->length && markpos < 0)
         return getInIfOpen()->read(bytes, off, num);
      
      fill();
      avail = count - pos;
      if(avail <= 0) return -1;
   }
   
   vint cnt = (avail < num) ? avail : num;
   bytes->copy(off, getBufIfOpen(), pos, cnt);
   pos += cnt;
   return cnt;
}

vint BufferedInputStream::available()
{
   return getInIfOpen()->available() + (count - pos);
}

vlong BufferedInputStream::skip(vlong n)
{
   getBufIfOpen(); // Check for closed stream
   
   if(n <= 0)
      return 0;
   
   vlong avail = count - pos;
   
   if(avail <= 0)
   {
      // If no mark position set then don't keep in buffer
      if(markpos <0)
         return getInIfOpen()->skip(n);
      
      // Fill in buffer to save bytes for reset
      fill();
      avail = count - pos;
      if(avail <= 0)
         return 0;
   }
   
   vlong skipped = (avail < n) ? avail : n;
   pos += skipped;
   return skipped;
}

void BufferedInputStream::mark(vint readlimit)
{
   marklimit = readlimit;
   markpos = pos;
}

void BufferedInputStream::reset()
{
   getBufIfOpen(); // Cause exception if closed
   
   if(markpos < 0)
      ex_throw new IOException("Resetting to invalid mark");
   
   pos = markpos;
}

vbool BufferedInputStream::markSupported()
{
   return true;
}

void BufferedInputStream::close()
{
   RArray<vint> buffer = buf;
   
   if(buffer != nullref)
   {
      buf = nullref;
      RInputStream input = in;
      in = nullref;
      
      if(input != nullref)
         input->close();
   }
}

} /* namespace io */

} /* namespace aro */
