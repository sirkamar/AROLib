#ifndef IO_STRINGINPUTSTREAM_H
#define IO_STRINGINPUTSTREAM_H

#include <aro/io/InputStream.h>

namespace aro {

namespace io {

class StringInputStream;
typedef Ref<StringInputStream> RStringInputStream;

class StringInputStream : public InputStream
{
   public:
      StringInputStream(RString s);
      
      virtual void close();
      
      virtual void reset();
      virtual vint available();
      virtual vlong skip(vlong n);
      virtual vbool markSupported();
      virtual void mark(vint readLimit);
      
      virtual vint read();
      virtual vint read(RArray<vint> bytes);
      virtual vint read(RArray<vint> bytes,vint offset,vint num);
   
   private:
      vint sMark, next;
      RArray<vint> bytes;
      
      void ensureOpen();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_STRINGINPUTSTREAM_H */
