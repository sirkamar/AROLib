#ifndef IO_DATAINPUTSTREAM_H
#define IO_DATAINPUTSTREAM_H

#include <aro/io/FilterInputStream.h>

namespace aro {

namespace io {

class DataInputStream;
typedef Ref<DataInputStream> RDataInputStream;

class DataInputStream : public FilterInputStream
{
   public:
      DataInputStream(RInputStream in);
      
      virtual vint read(RArray<vint> bytes,vint offset,vint num);
      virtual vint read(RArray<vint> bytes);
      virtual vint read();
      
      void readFully(RArray<vint> bytes);
      void readFully(RArray<vint> bytes,vint offset,vint num);
      
      vdouble readDouble();
      vshort readShort();
      vfloat readFloat();
      vlong readLong();
      vchar readChar();
      vbool readBool();
      vint readInt();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_DATAINPUTSTREAM_H */
