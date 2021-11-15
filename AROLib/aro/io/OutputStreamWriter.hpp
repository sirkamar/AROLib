#ifndef IO_OUTPUTSTREAMWRITER_H
#define IO_OUTPUTSTREAMWRITER_H

#include <aro/io/Writer.hpp>
#include <aro/io/OutputStream.hpp>

namespace aro {

namespace io {

class OutputStreamWriter;
typedef Ref<OutputStreamWriter> ROutputStreamWriter;

class OutputStreamWriter : public Writer
{
   public:
      OutputStreamWriter(ROutputStream out);

      virtual void write(vint c);
      virtual void write(RString str, vint off, vint num);
      virtual void write(RArray<vchar> cbuf, vint off, vint num);
      
      virtual void flush();
      virtual void close();

   private:
      ROutputStream os;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_OUTPUTSTREAMWRITER_H */
