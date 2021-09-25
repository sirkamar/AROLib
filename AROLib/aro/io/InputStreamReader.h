#ifndef IO_INPUTSTREAMREADER_H
#define IO_INPUTSTREAMREADER_H

#include <aro/io/reader.h>
#include <aro/io/InputStream.h>

namespace aro {

namespace io {

class InputStreamReader;
typedef Ref<InputStreamReader> RInputStreamReader;

class InputStreamReader : public Reader
{
   public:
      InputStreamReader(RInputStream in);

      virtual vint read();
      virtual vint read(RArray<vchar> cbuf, vint off, vint len);

      virtual vbool ready();
      virtual void close();

   private:
      RInputStream is;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_INPUTSTREAMREADER_H */
