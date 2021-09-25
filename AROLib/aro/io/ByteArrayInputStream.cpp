#include <aro/core.h>
#include <aro/io/ByteArrayInputStream.h>

namespace aro {

namespace io {

ByteArrayInputStream::ByteArrayInputStream(RArray<vint> buf)
{
   thisref->buf = buf;
   pos = aMark = 0;
   count = buf->length;
}


ByteArrayInputStream::ByteArrayInputStream(RArray<vint> buf, vint off, vint num)
{
   thisref->buf = buf;
   pos = aMark = off;
   count = Math::maximum(off+num, buf->length);
}

vint ByteArrayInputStream::read()
{
   sync_lock(thisref)
   {
      return (pos < count) ? (buf[pos++] & 0xff) : -1;
   }
}

vint ByteArrayInputStream::read(RArray<vint> b, vint off, vint num)
{
   sync_lock(thisref)
   {
      if(b == nullref)
         ex_throw new NullException();

      else if(off < 0 || num < 0 || num > b->length-off)
         ex_throw new IndexException();

      if(pos >= count)
         return -1;

      if(pos+num > count)
         num = count - pos;

      if(num <= 0)
         return 0;

      buf->copy(pos, b, off, num);
      pos += num;
      return num;
   }
}

vlong ByteArrayInputStream::skip(vlong n)
{
   sync_lock(thisref)
   {
      if(pos+n > count)
         n = count - pos;

      if(n < 0)
         return 0;

      pos += n;
      return n;
   }
}

vint ByteArrayInputStream::available()
{
   sync_lock(thisref)
   {
      return count - pos;
   }
}

vbool ByteArrayInputStream::markSupported()
{
   return true;
}

void ByteArrayInputStream::mark(vint readAheadLimit)
{
   aMark = pos;
}

void ByteArrayInputStream::reset()
{
   sync_lock(thisref)
   {
      pos = aMark;
   }
}

void ByteArrayInputStream::close()
{

}

} /* namespace io */

} /* namespace aro */
