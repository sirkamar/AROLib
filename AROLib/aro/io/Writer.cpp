#include <aro/core.hpp>
#include <aro/io/Writer.hpp>

namespace aro {

namespace io {

Writer::Writer()
   :writeBufferSize(1024)
{
   lock = thisref;
}

Writer::Writer(RObject lock)
   :writeBufferSize(1024)
{
   if(lock == nullref)
      ex_throw new NullException();

   thisref->lock = lock;
}

void Writer::write(vint c)
{
   sync_lock(lock)
   {
      if(writeBuffer == nullref)
         writeBuffer = new Array<vchar>(writeBufferSize);

      writeBuffer[0] = (vchar) c;

      write(writeBuffer, 0, 1);
   }
}

void Writer::write(RArray<vchar> cbuf)
{
   write(cbuf, 0, cbuf->length);
}

void Writer::write(RString str)
{
   write(str, 0, str->length());
}

void Writer::write(RString str, vint off, vint len)
{
   sync_lock(lock)
   {
      RArray<vchar> cbuf;

      if(len <= writeBufferSize)
      {
         if(writeBuffer == nullref)
            writeBuffer = new Array<vchar>(writeBufferSize);

         cbuf = writeBuffer;
      }
      else
         cbuf = new Array<vchar>(len);

      str->getChars(off, off+len, cbuf, 0);

      write(cbuf, 0, len);
   }
}

} /* namespace io */

} /* namespace aro */
