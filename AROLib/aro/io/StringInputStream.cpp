#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/StringInputStream.hpp>

namespace aro {

namespace io {

StringInputStream::StringInputStream(RString s)
{
   bytes = new Array<vint>(s->length()*2);
   
   //vchar is 2 bytes so write one byte on first read
   //then next byte on second read (i.e. 2 reads - 1 vchar)
   for(vint n=0; n<bytes->length; n+=2)
   {
      vchar c = s->charAt(n/2);
      bytes[n] = (c >> 8) & 0xFF;
      bytes[n+1] = (c >> 0) & 0xFF;
   }
   
   next = sMark = 0;
}

void StringInputStream::ensureOpen()
{
   if(bytes == nullref)
      ex_throw new IOException("Stream closed");
}

vint StringInputStream::read()
{
   ensureOpen();
   
   if(next >= bytes->length)
      return -1;
   
   return bytes[next++];
}

vint StringInputStream::read(RArray<vint> buf)
{
   return read(buf, 0, buf->length);
}

vint StringInputStream::read(RArray<vint> buf, vint off, vint num)
{
   ensureOpen();
   
   if(off < 0 || off > buf->length || num < 0 ||
      (off+num < buf->length) || (off+num < 0))
      ex_throw new IndexException();
   else if(num == 0)
      return 0;
   
   if(next >= bytes->length)
      return -1;
   
   vint n = Math::minimum(bytes->length-next, num);
   buf->copy(off, bytes, next, n);
   next += n;
   
   return n;
}

vlong StringInputStream::skip(vlong ns)
{
   ensureOpen();
   
   if(ns < 0)
      return 0;
   
   if(ns > bytes->length-next)
      ns = bytes->length-next;
   
   next += ns;
   
   return ns;
}

vint StringInputStream::available()
{
   return bytes->length-next;
}

void StringInputStream::reset()
{
   ensureOpen();
   next = sMark;
}

vbool StringInputStream::markSupported()
{
   return true;
}

void StringInputStream::mark(vint readLimit)
{
   if(readLimit < 0)
      ex_throw new ArgumentException("Read limit < 0");
   
   ensureOpen();
   sMark = next;
}

void StringInputStream::close()
{
   bytes = nullref;
}

} /* namespace io */

} /* namespace aro */
