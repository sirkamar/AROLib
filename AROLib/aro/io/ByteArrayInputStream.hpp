#ifndef IO_BYTEARRAYINPUTSTREAM_H
#define IO_BYTEARRAYINPUTSTREAM_H

#include <aro/io/InputStream.hpp>

namespace aro {

namespace io {

class ByteArrayInputStream;
typedef Ref<ByteArrayInputStream> RByteArrayInputStream;

class ByteArrayInputStream extends public InputStream
{
   public:
      ByteArrayInputStream(RArray<vint> buf);
      ByteArrayInputStream(RArray<vint> buf, vint off, vint num);
      
      vint read(RArray<vint> b, vint off, vint num);
      void mark(vint readAheadLimit);
      vbool markSupported();
      vlong skip(vlong n);
      vint available();
      void reset();
      void close();
      vint read();
      
   protected:
      RArray<vint> buf;
      vlong pos, aMark;
      vint count;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_BYTEARRAYINPUTSTREAM_H */
