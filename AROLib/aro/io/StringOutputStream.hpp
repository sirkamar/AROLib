#ifndef IO_STRINGOUTPUTSTREAM_H
#define IO_STRINGOUTPUTSTREAM_H

#include <aro/io/OutputStream.hpp>
#include <aro/core/StringBuffer.hpp>

namespace aro {

namespace io {

class StringOutputStream;
typedef Ref<StringOutputStream> RStringOutputStream;

class StringOutputStream extends public OutputStream
{
   public:
      StringOutputStream();
      StringOutputStream(vint initialSize);
      
      virtual void close();
      virtual void flush();
      
      virtual void write(vint byte);
      virtual void write(RArray<vint> bytes);
      virtual void write(RArray<vint> bytes,vint offset,vint num);
      
      virtual RStringBuffer getBuffer();
      virtual RString toString();
   
   private:
      vint temp;
      vbool tempSet;
      RStringBuffer buf;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_STRINGOUTPUTSTREAM_H */
