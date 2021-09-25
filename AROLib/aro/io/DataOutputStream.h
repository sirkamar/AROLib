#ifndef IO_DATAOUTPUTSTREAM_H
#define IO_DATAOUTPUTSTREAM_H

#include <aro/io/FilterOutputStream.h>

namespace aro {

namespace io {

class DataOutputStream;
typedef Ref<DataOutputStream> RDataOutputStream;

class DataOutputStream : public FilterOutputStream
{
   public:
      DataOutputStream(ROutputStream os);
      
      virtual void write(RArray<vint> bytes,vint offset,vint num);
      virtual void write(RArray<vint> bytes);
      virtual void write(vint byte);
      
      virtual void flush();
      
      void writeDouble(vdouble d);
      void writeShort(vshort s);
      void writeFloat(vfloat f);
      void writeLong(vlong l);
      void writeChar(vchar c);
      void writeBool(vbool b);
      void writeInt(vint i);
      
      vint size(); // number of bytes written
   
   protected:
      vint written;
   
   private:
      void incCount(vint value);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_DATAOUTPUTSTREAM_H */
