#ifndef IO_FILTERWRITER_H
#define IO_FILTERWRITER_H

#include <aro/io/Writer.h>

namespace aro {

namespace io {

class FilterWriter;
typedef Ref<FilterWriter> RFilterWriter;

class FilterWriter :  public Writer
{
   public:
      FilterWriter(RWriter out);
      
      virtual void write(vint c);
      virtual void write(RString str, vint off, vint num);
      virtual void write(RArray<vchar> cbuf, vint off, vint num);

      virtual void flush();
      virtual void close();

   protected:
      RWriter out;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILTERWRITER_H */
