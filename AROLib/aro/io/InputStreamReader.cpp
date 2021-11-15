#include <aro/core.hpp>
#include <aro/io/InputStreamReader.hpp>

namespace aro {

namespace io {

InputStreamReader::InputStreamReader(RInputStream in)
   :Reader(in)
{
   is = in;
}


vint InputStreamReader::read()
{
   vint ch1 = is->read();
   vint ch2 = is->read();
   
   if((ch1|ch2) < 0)
      return -1;
   
   return ((ch1 << 8) + (ch2 << 0));
}

vint InputStreamReader::read(RArray<vchar> cbuf, vint off, vint num)
{
   if(off < 0 || off > cbuf->length || num < 0 ||
      (off+num < cbuf->length) || (off+num < 0))
      ex_throw new IndexException();

   else if(num == 0)
      return 0;

   for(vint n=0, amt=0; n<num; n++, amt++)
   {
      vint ch1 = is->read();
      vint ch2 = is->read();

      // if end of file terminate read and
      // return what was read so far.
      if((ch1|ch2) < 0)
      {
         if(amt == 0)
            return -1;
         else
            return amt;
      }

      cbuf[off+n] = (vchar) ((ch1 << 8) + (ch2 << 0));
   }

   return num;
}

vbool InputStreamReader::ready()
{
   return is->available() > 0;
}

void InputStreamReader::close()
{
   is->close();
}

} /* namespace io */

} /* namespace aro */
