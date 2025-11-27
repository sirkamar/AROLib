#ifndef IO_OUTPUTSTREAM_H
#define IO_OUTPUTSTREAM_H

#include <aro/core/String.hpp>

namespace aro {

namespace io {

class OutputStream;
typedef Ref<OutputStream> ROutputStream;

class OutputStream extends public Object
{
   public:
      virtual void close(); // closes the stream for Output
      virtual void flush(); // forces any buffered output bytes to be written out
      
      virtual void write(vint byte)=0; // writes one byte to the stream
      virtual void write(RArray<vint> bytes); // writes a sequence of bytes
      virtual void write(RArray<vint> bytes,vint offset,vint num); // writes a specified series of bytes      
   
   protected:
      virtual void finalize(); // ensure stream closed
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_OUTPUTSTREAM_H */
