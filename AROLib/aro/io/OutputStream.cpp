#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/OutputStream.hpp>

namespace aro {

namespace io {

void OutputStream::close()
{
   
}

void OutputStream::flush()
{
   
}

void OutputStream::write(RArray<vint> arr)
{
   write(arr, 0, arr->length);
}

void OutputStream::write(RArray<vint> arr, vint off, vint num)
{
   if(arr == nullref)
      ex_throw new NullException();
   
   else if(off < 0 || num < 0 || num > arr->length - off)
      ex_throw new IndexException("Index out of bounds");
   
   if(num == 0)
      return;
   
   for(vint i=0; i<num; i++)
      write(arr[off + i]);
}

void OutputStream::finalize()
{
   ex_try
   {
      close();
   }
   ex_catch
   {
      ex_handle(IOException)
      {
         // Do nothing here
      }
   }
   ex_end
   
   Object::finalize();
}

} /* namespace io */

} /* namespace aro */
