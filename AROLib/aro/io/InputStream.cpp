#include <aro/core.h>
#include <aro/io/InputStream.h>
#include <aro/io/IOException.h>

namespace aro {

namespace io {

const vint InputStream::SKIP_BUFFER_SIZE = 2048;

RArray<vint> InputStream::skipBuffer;

void InputStream::reset()
{
   ex_throw new IOException("mark/reset not supported");
}

vint InputStream::available()
{
   return 0;
}

vlong InputStream::skip(vlong n)
{
   vlong remaining = n;
   vint nr;
   if(skipBuffer == nullref)
      skipBuffer = new Array<vint>(SKIP_BUFFER_SIZE);
   
   RArray<vint> localSkipBuffer = skipBuffer;
   
   if(n <= 0)
      return 0;
   
   while(remaining > 0)
   {
      nr = read(localSkipBuffer, 0,
            (vint) Math::minimum((vlong)SKIP_BUFFER_SIZE, remaining));
      if(nr < 0)
         break;
      
      remaining -= nr;
   }
   
   return n - remaining;
}

vbool InputStream::markSupported()
{
   return false;
}

void InputStream::mark(vint readlimit)
{
   
}

vint InputStream::read(RArray<vint> arr)
{
   return read(arr, 0, arr->length);
}

vint InputStream::read(RArray<vint> arr, vint off, vint num)
{
   if(arr == nullref)
      ex_throw new NullException();
   
   else if(off < 0 || num < 0 || num > arr->length - off)
      ex_throw new IndexException("Index out of bounds");
   
   else if(num == 0)
      return 0;
   
   vint c = read();
   if (c == -1)
       return -1;
   
   arr[off] = c;
   
   vint i = 1;
   
   ex_try
   {
      for(; i<num; i++)
      {
         c = read();
         if(c == -1)
            break;
         
         arr[off+i] = c;
      }
   }
   ex_catch
   {
      ex_handle(IOException)
      {
         // do nothing
      }
   }
   ex_end
   
   return i;
}

void InputStream::close()
{
   
}

void InputStream::finalize()
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
