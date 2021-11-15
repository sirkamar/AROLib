#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/StringReader.hpp>

namespace aro {

namespace io {

StringsReader::StringsReader(RString s)
{
   str = s;
   next = sMark = 0;
   length = s->length();
}

void StringsReader::ensureOpen()
{
   if(str == nullref)
      ex_throw new IOException("Stream closed");
}

vint StringsReader::read()
{
   sync_lock(lock)
   {
      ensureOpen();

      if(next >= length)
         return -1;

      return str->charAt(next++);
   }
}

vint StringsReader::read(RArray<vchar> cbuf, vint off, vint num)
{
   sync_lock(lock)
   {
      ensureOpen();

      if((off < 0) || (off > cbuf->length) || (num < 0) ||
            ((off + num) > cbuf->length) || ((off + num) < 0))
         ex_throw new IndexException();
      
      else if(num == 0)
         return 0;
      
      if(next >= length)
         return -1;

      vint n = Math::minimum((vint)(length - next), num);
      str->getChars(next, next + n, cbuf, off);
      next += n;
      
      return n;
   }
}

vlong StringsReader::skip(vlong ns)
{
   sync_lock(lock)
   {
      ensureOpen();

      if(next >= length)
         return 0;

      // Bound skip by beginning and end of the source
      vlong n = Math::minimum((vlong)length - next, ns);
      n = Math::maximum((vlong)-next, n);
      next += n;
      return n;
   }
}

vbool StringsReader::ready()
{
   sync_lock(lock)
   {
      ensureOpen();

      return true;
   }
}

vbool StringsReader::markSupported()
{
   return true;
}

void StringsReader::mark(vint readAheadLimit)
{
   if (readAheadLimit < 0)
      ex_throw new ArgumentException("Read-ahead limit < 0");

   sync_lock(lock)
   {
      ensureOpen();

      sMark = next;
   }
}

void StringsReader::reset()
{
   sync_lock(lock)
   {
      ensureOpen();

      next = sMark;
   }
}

void StringsReader::close()
{
   str = nullref;
}

} /* namespace io */

} /* namespace aro */
