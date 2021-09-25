#ifndef IO_FILTERINPUTSTREAM_H
#define IO_FILTERINPUTSTREAM_H

#include <aro/io/InputStream.h>

namespace aro {

namespace io {

class FilterInputStream;
typedef Ref<FilterInputStream> RFilterInputStream;

class FilterInputStream : public InputStream
{
   public:
      virtual void close();
      
      virtual void reset();
      virtual vint available();
      virtual vlong skip(vlong n);
      virtual vbool markSupported();
      virtual void mark(vint readLimit);
      
      virtual vint read();
      virtual vint read(RArray<vint> bytes);
      virtual vint read(RArray<vint> bytes,vint offset,vint num);
   
   protected:
      RInputStream in;
      
      FilterInputStream(RInputStream is);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILTERINPUTSTREAM_H */
