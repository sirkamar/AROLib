#ifndef IO_FILTEROUTPUTSTREAM_H
#define IO_FILTEROUTPUTSTREAM_H

#include <aro/io/OutputStream.hpp>

namespace aro {

namespace io {

class FilterOutputStream;
typedef Ref<FilterOutputStream> RFilterOutputStream;

class FilterOutputStream extends public OutputStream
{
   public:
      virtual void close();
      virtual void flush();
      
      virtual void write(vint byte);
      virtual void write(RArray<vint> bytes);
      virtual void write(RArray<vint> bytes,vint offset,vint num);
      
   
   protected:
      ROutputStream out;
      
      FilterOutputStream(ROutputStream out);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILTEROUTPUTSTREAM_H */
