#include <aro/core.hpp>
#include <aro/io/StringOutputStream.hpp>

namespace aro {

namespace io {

StringOutputStream::StringOutputStream()
{
   buf = new StringBuffer();
   tempSet = false;
   temp = 0;
}

StringOutputStream::StringOutputStream(vint size)
{
   if(size < 0)
      ex_throw new ArgumentException("Negative buffer size");
   
   buf = new StringBuffer(size);
   tempSet = false;
   temp = 0;
}

void StringOutputStream::write(vint byte)
{
   if(!tempSet)
      temp = byte;
   else
      buf->append((vchar)((temp << 8) + (byte << 0)));
   
   tempSet = !tempSet;
}

void StringOutputStream::write(RArray<vint> bytes)
{
   write(bytes, 0, bytes->length);
}

void StringOutputStream::write(RArray<vint> bytes, vint off, vint num)
{
   if(off < 0 || off > bytes->length || num < 0 ||
      (off+num > bytes->length) || (off+num < 0))
      ex_throw new IndexException();
   
   else if(num == 0)
      return;
   
   for(vint n=0; n<bytes->length; n++)
   {
      if(!tempSet)
         temp = bytes[n];
      else
         buf->append((vchar)((temp << 8)+(bytes[n] << 0)));
      
      tempSet = !tempSet;
   }
}

RStringBuffer StringOutputStream::getBuffer()
{
   return buf;
}

RString StringOutputStream::toString()
{
   return buf->toString();
}

void StringOutputStream::flush()
{
   
}

void StringOutputStream::close()
{
   
}
} /* namespace io */

} /* namespace aro */
