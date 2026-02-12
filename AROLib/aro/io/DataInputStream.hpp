#ifndef IO_DATAINPUTSTREAM_H
#define IO_DATAINPUTSTREAM_H

#include <aro/io/FilterInputStream.hpp>

namespace aro {

namespace io {

class DataInputStream;
typedef Ref<DataInputStream> RDataInputStream;

class DataInputStream extends public FilterInputStream
{
   public:
      DataInputStream(RInputStream in);
      
      virtual vint read(RArray<vint> bytes,vint offset,vint num) final;
      virtual vint read(RArray<vint> bytes) final;
      
      virtual void readFully(RArray<vint> bytes) final;
      virtual void readFully(RArray<vint> bytes,vint offset,vint num) final;
      
      virtual vdouble readDouble() final;
      virtual vshort readShort() final;
      virtual vfloat readFloat() final;
      virtual vlong readLong() final;
      virtual vchar readChar() final;
      virtual vbool readBool() final;
      virtual vint readInt() final;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_DATAINPUTSTREAM_H */
