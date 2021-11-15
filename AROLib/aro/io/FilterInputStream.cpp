#include <aro/core.hpp>
#include <aro/io/FilterInputStream.hpp>

namespace aro {

namespace io {

FilterInputStream::FilterInputStream(RInputStream is)
{
   in = is;
}

vint FilterInputStream::read()
{
   return in->read();
}

vint FilterInputStream::read(RArray<vint> bytes)
{
   return read(bytes, 0, bytes->length);
}

vint FilterInputStream::read(RArray<vint> bytes, vint off, vint num)
{
   return in->read(bytes, off, num);
}

vlong FilterInputStream::skip(vlong n)
{
   return in->skip(n);
}

vint FilterInputStream::available()
{
   return in->available();;
}

vbool FilterInputStream::markSupported()
{
   return in->markSupported();
}

void FilterInputStream::mark(vint readLimit)
{
   in->mark(readLimit);
}

void FilterInputStream::reset()
{
   in->reset();
}

void FilterInputStream::close()
{
   in->close();
}

} /* namespace io */

} /* namespace aro */
