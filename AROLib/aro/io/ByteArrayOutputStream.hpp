#ifndef IO_BYTEARRAYOUTPUTSTREAM_H
#define IO_BYTEARRAYOUTPUTSTREAM_H

#include <aro/io/OutputStream.hpp>

namespace aro {

namespace io {

class ByteArrayOutputStream;
typedef Ref<ByteArrayOutputStream> RByteArrayOutputStream;

class ByteArrayOutputStream extends public OutputStream
{
   public:
      ByteArrayOutputStream();
      ByteArrayOutputStream(vint size);
      
      void write(RArray<vint> buf, vint off, vint num);
      void writeTo(ROutputStream out);
      RArray<vint> toByteArray();
      RString toString();
      void write(vint b);
      void close();
      void reset();
      vint size();

   protected:
      RArray<vint> buf;
      vint count;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_BYTEARRAYOUTPUTSTREAM_H */
