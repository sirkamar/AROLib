#ifndef IO_STREAMABLE_H
#define IO_STREAMABLE_H

#include <aro/io/StreamBase.h>
#include <aro/core/Cloneable.h>

namespace aro {

namespace io {

//template <class T>
//interface Streamable;

template <class T>
using RStreamable = Ref<Streamable<T>>;

/* A class implementing this interface must
provide a no-argument constructor so as to
enable the Streamable API to re-create an
object instance of the class from the
stream. The constructor may be set as
private access, however, in such case
interface Streamable<T> must be a friend.
Note:
The readObject() function doesn't actually
violate the immutableness of immutabe objects
since it is in essence "constructing" the object.
As such the readObject() function is considered to
be a pseudo-constructor. */
template <class T>
interface Streamable : StreamBase
{
   vlong getObjectVersion(); // default 1L
   
   void readObject(RObjectInputStream is) = 0;
   
   void writeObject(RObjectOutputStream os) = 0;
   
   protected:
      Streamable();
   
   private:
      struct Builder
      {
          Builder();
          void init() const;
          static RObject create();
      };

      static const Builder BUILDER;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_STREAMABLE_H */
