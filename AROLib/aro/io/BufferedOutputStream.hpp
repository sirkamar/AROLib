#ifndef IO_BUFFEREDOUTPUTSTREAM_H
#define IO_BUFFEREDOUTPUTSTREAM_H

#include <aro/io/FilterOutputStream.hpp>

namespace aro {

namespace io {

class BufferedOutputStream;
typedef Ref<BufferedOutputStream> RBufferedOutputStream;

class BufferedOutputStream extends public FilterOutputStream
{
   public:
      BufferedOutputStream(ROutputStream os);
      BufferedOutputStream(ROutputStream os, vint size);
      
      void write(vint byte);
      void write(RArray<vint> bytes);
      void write(RArray<vint> bytes,vint off,vint num);
      
      void flush();
   
   protected:
      vint count;
      RArray<vint> buf;
   
   private:
      void flushBuffer();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_BUFFEREDOUTPUTSTREAM_H */
