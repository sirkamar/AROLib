#ifndef IO_STRINGREADER_H
#define IO_STRINGREADER_H

#include <aro/io/Reader.hpp>

namespace aro {

namespace io {

class StringsReader;
typedef Ref<StringsReader> RStringsReader;

class StringsReader :  public Reader
{
   public:
      StringsReader(RString str);
      
      virtual vint read();
      virtual vint read(RArray<vchar> cbuf, vint off, vint num);

      virtual void mark(vint readAheadLimit);
      virtual vbool markSupported();
      virtual vlong skip(vlong n);
      virtual void reset();
      virtual vbool ready();
      virtual void close();

   private:
      vint length;
      RString str;
      vlong next, sMark;

      void ensureOpen();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_STRINGREADER_H */
