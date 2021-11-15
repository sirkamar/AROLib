#include <aro/core.hpp>
#include <aro/io/FilterReader.hpp>

namespace aro {

namespace io {

FilterReader::FilterReader(RReader in)
   :Reader(in)
{
   thisref->in = in;
}


vint FilterReader::read()
{
   return in->read();
}

vint FilterReader::read(RArray<vchar> cbuf, vint off, vint num)
{
   return in->read(cbuf, off, num);
}

vlong FilterReader::skip(vlong n)
{
   return in->skip(n);
}

vbool FilterReader::ready()
{
   return in->ready();
}

vbool FilterReader::markSupported()
{
   return in->markSupported();
}

void FilterReader::mark(vint readAheadLimit)
{
   in->mark(readAheadLimit);
}

void FilterReader::reset()
{
   in->reset();
}

void FilterReader::close()
{
   in->close();
}

} /* namespace io */

} /* namespace aro */
