#ifndef IO_BUFFEREDINPUTSTREAM_H
#define IO_BUFFEREDINPUTSTREAM_H

#include <aro/io/FilterInputStream.hpp>

namespace aro {

namespace io {

class BufferedInputStream;
typedef Ref<BufferedInputStream> RBufferedInputStream;

class BufferedInputStream : public FilterInputStream
{
   public:
      BufferedInputStream(RInputStream is);
      BufferedInputStream(RInputStream is, vint size);
      
      vint read();
      vint read(RArray<vint> bytes);
      vint read(RArray<vint> bytes, vint off, vint num);
      
      vint available();
      vlong skip(vlong n);
      void mark(vint readlimit);
      void reset();
      vbool markSupported();
      void close();
      
   protected:
      RArray<vint> buf;
      vint count, pos, markpos, marklimit;
   
   private:
      static const vint defaultBufSize;
      
      vint read1(RArray<vint>,vint,vint);
      RInputStream getInIfOpen();
      RArray<vint> getBufIfOpen();
      void fill();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_BUFFEREDINPUTSTREAM_H */
