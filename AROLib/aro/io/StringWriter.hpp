#ifndef IO_STRINGWRITER_H
#define IO_STRINGWRITER_H

#include <aro/io/Writer.hpp>
#include <aro/core/StringBuffer.hpp>

namespace aro {

namespace io {

class StringsWriter;
typedef Ref<StringsWriter> RStringsWriter;

class StringsWriter extends public Writer
{
   public:
      StringsWriter();
      StringsWriter(vint size);

      virtual void write(vint c);
      virtual void write(RString str);
      virtual void write(RString str, vint off, vint num);
      virtual void write(RArray<vchar> cbuf, vint off, vint num);

      virtual RStringBuffer getBuffer();
      virtual RString toString();
      virtual void flush();
      virtual void close();

   private:
      RStringBuffer buf;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_STRINGWRITER_H */
