#ifndef IO_READER_H
#define IO_READER_H

#include <aro/core.hpp>

namespace aro {

namespace io {

class Reader;
typedef Ref<Reader> RReader;

class Reader extends public Object
{
   public:
      virtual vint read();
      virtual vint read(RArray<vchar> cbuf);
      virtual vint read(RArray<vchar> cbuf, vint off, vint len)=0;

      virtual void mark(vint readAheadLimit);
      virtual vbool markSupported();
      virtual vlong skip(vlong n);
      virtual void close()=0;
      virtual void reset();
      virtual vbool ready();

   protected:
      RObject lock;
      
      Reader();
      Reader(RObject lock);

   private:
      RArray<vchar> skipBuffer;
      static const vint maxSkipBufferSize;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_READER_H */
