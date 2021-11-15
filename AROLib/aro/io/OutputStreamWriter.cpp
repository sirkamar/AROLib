#include <aro/core.hpp>
#include <aro/io/OutputStreamWriter.hpp>

namespace aro {

namespace io {

OutputStreamWriter::OutputStreamWriter(ROutputStream out)
   :Writer(out)
{
   os = out;
}


void OutputStreamWriter::write(vint c)
{
   os->write((c >> 8) & 0xFF);
   os->write((c >> 0) & 0xFF);
}

void OutputStreamWriter::write(RString str, vint off, vint num)
{
   if(off < 0 || off > str->length() || num < 0 ||
      (off+num < str->length()) || (off+num < 0))
      ex_throw new IndexException();

   for(vint n=0; n<num; n++)
      write(str->charAt(off+n));
}

void OutputStreamWriter::write(RArray<vchar> cbuf, vint off, vint num)
{
   if(off < 0 || off > cbuf->length || num < 0 ||
      (off+num < cbuf->length) || (off+num < 0))
      ex_throw new IndexException();
   
   for(vint n=0; n<num; n++)
      write(cbuf[off+n]);
}

void OutputStreamWriter::flush()
{
   os->flush();
}

void OutputStreamWriter::close()
{
   os->close();
}

} /* namespace io */

} /* namespace aro */
