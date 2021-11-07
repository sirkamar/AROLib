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
enable the AROLib API to instaniate an
object instance of the class. The 
constructor may be set as private
access, however, in such case
interface Cloneable<T> must
be a friend. */
template <class T>
interface Cloneable : Interface
{
   protected:
      Cloneable();
   
   private:
      static const Class<T> TYPEID;
};

} /* namespace aro */

#endif /* CORE_CLONEABLE_H */
