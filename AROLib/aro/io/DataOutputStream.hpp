#ifndef IO_DATAOUTPUTSTREAM_H
#define IO_DATAOUTPUTSTREAM_H

#include <aro/io/FilterOutputStream.hpp>

namespace aro {

namespace io {

class DataOutputStream;
typedef Ref<DataOutputStream> RDataOutputStream;

class DataOutputStream extends public FilterOutputStream
{
   public:
      DataOutputStream(ROutputStream os);
      
      virtual void write(RArray<vint> bytes,vint offset,vint num);
      virtual void write(vint byte);
      
      virtual void flush();
      
      virtual void writeDouble(vdouble d) final;
      virtual void writeShort(vshort s) final;
      virtual void writeFloat(vfloat f) final;
      virtual void writeLong(vlong l) final;
      virtual void writeChar(vchar c) final;
      virtual void writeBool(vbool b) final;
      virtual void writeInt(vint i) final;
      
      virtual vint size() final; // number of bytes written
   
   protected:
      vint written;
   
   private:
      void incCount(vint value);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_DATAOUTPUTSTREAM_H */
