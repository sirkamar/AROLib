#include <aro/core.h>
#include <aro/io/BufferedOutputStream.h>

namespace aro {

namespace io {

BufferedOutputStream::BufferedOutputStream(ROutputStream os)
   :FilterOutputStream(os)
{
   count = 0;
   buf = new Array<vint>(8192);
}

BufferedOutputStream::BufferedOutputStream(ROutputStream os, vint size)
   :FilterOutputStream(os)
{
   if(size <= 0)
      ex_throw new ArgumentException("Buffer size <= 0");
   
   count = 0;
   buf = new Array<vint>(size);
}

void BufferedOutputStream::flushBuffer()
{
   if(count > 0)
   {
      out->write(buf, 0, count);
      count = 0;
   }
}

void BufferedOutputStream::write(vint byte)
{
   //if(count >= buf->length)
   //   flushBuffer();
   
   buf[count++] = byte;
   
   if(count >= buf->length)
      flushBuffer();
}

void BufferedOutputStream::write(RArray<vint> bytes)
{
   write(bytes, 0, bytes->length);
}

void BufferedOutputStream::write(RArray<vint> bytes, vint off, vint num)
{
   if(num >= buf->length)
   {
      //If the request length exceeds the size of the output buffer,
      //flush the output buffer and then write the data directly.
      //In this way buffered streams will cascade harmlessly.
      flushBuffer();
      out->write(bytes, off, num);
      return;
   }
   
   if(num > buf->length-count)
      flushBuffer();
   
   buf->copy(count, bytes, off, num);
   count += num;
   
   if(count >= buf->length)
      flushBuffer();
}

void BufferedOutputStream::flush()
{
   flushBuffer();
   out->flush();
}

} /* namespace io */

} /* namespace aro */
