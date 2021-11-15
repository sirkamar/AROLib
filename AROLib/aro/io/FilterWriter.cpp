#include <aro/core.hpp>
#include <aro/io/FilterWriter.hpp>

namespace aro {

namespace io {

FilterWriter::FilterWriter(RWriter out)
   :Writer(out)
{
   thisref->out = out;
}

void FilterWriter::write(vint c)
{
   out->write(c);
}

void FilterWriter::write(RArray<vchar> cbuf, vint off, vint num)
{
   out->write(cbuf, off, num);
}

void FilterWriter::write(RString str, vint off, vint num)
{
   out->write(str, off, num);
}

void FilterWriter::flush()
{
   out->flush();
}

void FilterWriter::close()
{
   out->close();
}

} /* namespace io */

} /* namespace aro */
