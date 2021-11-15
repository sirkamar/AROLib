#ifndef IO_INPUTSTREAM_H
#define IO_INPUTSTREAM_H

#include <aro/core/String.hpp>

namespace aro {

namespace io {

class InputStream;
typedef Ref<InputStream> RInputStream;

class InputStream : public Object
{
   public:
      virtual void close(); // closes the input stream
      
      virtual void reset(); // Repositions this stream to the last marked position
      virtual vint available(); // estimate of readable bytes w/o blocking
      virtual vlong skip(vlong n); // attempts to skip next n bytes
      virtual vbool markSupported(); // Tests if this input stream supports mark and reset
      virtual void mark(vint readLimit); // the maximum readable bytes before mark is invalid
      
      virtual vint read()=0; // reads one byte from the stream
      virtual vint read(RArray<vint> bytes); // reads a series of bytes
      virtual vint read(RArray<vint> bytes,vint offset,vint num); // reads a specified number of bytes
   
   protected:
      virtual void finalize(); // ensure stream closed
   
   private:
      static RArray<vint> skipBuffer;
      static const vint SKIP_BUFFER_SIZE;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_INPUTSTREAM_H */
