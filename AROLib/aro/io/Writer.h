#ifndef IO_WRITER_H
#define IO_WRITER_H

#include <aro/core.h>

namespace aro {

namespace io {

class Writer;
typedef Ref<Writer> RWriter;

class Writer : public Object
{
   public:
      virtual void write(vint c);
      virtual void write(RArray<vchar> cbuf);
      virtual void write(RArray<vchar> cbuf, vint off, vint num)=0;

      virtual void write(RString str, vint off, vint num);
      virtual void write(RString str);
      
      virtual void flush()=0;
      virtual void close()=0;

   protected:
      RObject lock;

      Writer();
      Writer(RObject lock);

   private:
      RArray<vchar> writeBuffer;
      const vint writeBufferSize;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_WRITER_H */
