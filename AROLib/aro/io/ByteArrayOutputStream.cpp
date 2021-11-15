#include <aro/core.hpp>
#include <aro/io/ByteArrayOutputStream.hpp>

namespace aro {

namespace io {

ByteArrayOutputStream::ByteArrayOutputStream()
{
   count = 0;
   buf = new Array<vint>(32);
}

ByteArrayOutputStream::ByteArrayOutputStream(vint size)
{
   if(size < 0)
      ex_throw new ArgumentException("Negative initial size: " + String::valueOf(size));

   count = 0;
   buf = new Array<vint>(size);
}

void ByteArrayOutputStream::write(vint b)
{
   sync_lock(thisref)
   {
      vint newCount = count + 1;

      if(newCount > buf->length)
         buf = buf->copyOf(Math::maximum(buf->length << 1, newCount));

      buf[count] = b;
      count = newCount;
   }
}

void ByteArrayOutputStream::write(RArray<vint> b, vint off, vint num)
{
   sync_lock(thisref)
   {
      if((off < 0 ) || (off > b->length) || (num < 0) ||
         ((off+num) > b->length) || ((off+num) < 0))
         ex_throw new IndexException();

      else if(num == 0)
         return;

      vint newCount = count + num;
      if(newCount > buf->length)
         buf = buf->copyOf(Math::maximum(buf->length << 1, newCount));

      buf->copy(count, b, off, num);
      count = newCount;
   }
}

void ByteArrayOutputStream::writeTo(ROutputStream out)
{
   sync_lock(thisref)
   {
      out->write(buf, 0, count);
   }
}

void ByteArrayOutputStream::reset()
{
   sync_lock(thisref)
   {
      count = 0;
   }
}

RArray<vint> ByteArrayOutputStream::toByteArray()
{
   sync_lock(thisref)
   {
      return buf->copyOf(count);
   }
}

vint ByteArrayOutputStream::size()
{
   sync_lock(thisref)
   {
      return count;
   }
}

RString ByteArrayOutputStream::toString()
{
   sync_lock(thisref)
   {
      // develop method of converting byte array
      // to string (or at least to vchar array
      // then, in turn, convert to string)
      
      return "ByteArrayOutputStream";
   }
}

void ByteArrayOutputStream::close()
{

}

} /* namespace io */

} /* namespace aro */
