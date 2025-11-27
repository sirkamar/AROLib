#ifndef IO_FILTERREADER_H
#define IO_FILTERREADER_H

#include <aro/io/Reader.hpp>

namespace aro {

namespace io {

class FilterReader;
typedef Ref<FilterReader> RFilterReader;

class FilterReader extends public Reader
{
   public:
      virtual vint read();
      virtual vint read(RArray<vchar> cbuf, vint off, vint num);

      virtual void mark(vint readAheadLimit);
      virtual vbool markSupported();
      virtual vlong skip(vlong n);
      virtual void reset();
      virtual vbool ready();
      virtual void close();

   protected:
      RReader in;

      FilterReader(RReader in);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILTERREADER_H */
