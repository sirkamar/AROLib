#include <aro/core.h>
#include <aro/core/Math.h>
#include <aro/io/Reader.h>
#include <aro/io/IOException.h>

namespace aro {

namespace io {

Reader::Reader()
{
   lock = thisref;
}


Reader::Reader(RObject lock)
{
   if(lock == nullref)
      ex_throw new NullException();

   thisref->lock = lock;
}

vint Reader::read()
{
   RArray<vchar> cb = new Array<vchar>(1);

   if(read(cb, 0, 1) == -1)
      return -1;
   else
      return cb[0];
}

vint Reader::read(RArray<vchar> cbuf)
{
   return read(cbuf, 0, cbuf->length);
}

const vint Reader::maxSkipBufferSize = 8192;

vlong Reader::skip(vlong n)
{
   if(n < 0L)
      ex_throw new ArgumentException("skip value is negative");

   vint nn = (vint) Math::minimum(n, (vlong)maxSkipBufferSize);

   sync_lock(lock)
   {
      if((skipBuffer == nullref) || (skipBuffer->length < nn))
         skipBuffer = new Array<vchar>(nn);

      vlong r = n;

      while(r > 0)
      {
         vint nc = read(skipBuffer, 0, (vint)Math::minimum(r, (vlong)nn));
         if(nc == -1)
            break;
         r -= nc;
      }

      return n - r;
   }
}

vbool Reader::ready()
{
   return false;
}

vbool Reader::markSupported()
{
   return false;
}

void Reader::mark(vint readAheadLimit)
{
   ex_throw new IOException("mark() not supported");
}

void Reader::reset()
{
   ex_throw new IOException("reset() not supported");
}

} /* namespace io */

} /* namespace aro */
