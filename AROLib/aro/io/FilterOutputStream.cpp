#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/FilterOutputStream.hpp>

namespace aro {

namespace io {

FilterOutputStream::FilterOutputStream(ROutputStream os)
{
   out = os;
}

void FilterOutputStream::close()
{
   ex_try
   {
      flush();
   }
   ex_catch
   {
      ex_handle(IOException)
      {
         // do nothing
      }
   }
   ex_end
   
   out->close();
}

void FilterOutputStream::flush()
{
   out->flush();
}

void FilterOutputStream::write(vint byte)
{
   out->write(byte);
}

void FilterOutputStream::write(RArray<vint> bytes)
{
   write(bytes, 0, bytes->length);
}

void FilterOutputStream::write(RArray<vint> bytes, vint off, vint num)
{
   if((off|num|(bytes->length-(num+off))|(off+num)) < 0)
      ex_throw new IndexException();
   
   for(vint i=0; i<num; i++)
      write(bytes[off+i]);
}

} /* namespace io */

} /* namespace aro */
