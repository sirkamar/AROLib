#ifndef CORE_CLONEABLE_H
#define CORE_CLONEABLE_H

#include <aro/core/utils/Class.h>

namespace aro {

template <class T>
interface Cloneable;

template <class T>
using RCloneable = Ref<Cloneable<T>>;

/* A class implementing this interface must
provide a no-argument constructor so as to
enable the Streamable API to re-create an
object instance of the class from the
stream. The constructor may be set as
private access, however, in such case
class Streamable<T> must be a friend. */
template <class T>
interface Cloneable : Interface
{
   protected:
      Cloneable();
   
   private:
      static const Class<T> CLONEID;
};

} /* namespace aro */

#endif /* CORE_CLONEABLE_H */
