#ifndef CORE_CLONEABLE_IMPL_H
#define CORE_CLONEABLE_IMPL_H

//#include <aro/core/Cloneable.h>
#include <aro/core/utils/Class-impl.h>

namespace aro {

template <class T>
const Class<T> Cloneable<T>::TYPEID = 1;

template <class T>
Cloneable<T>::Cloneable()
{
   TYPEID.init();
}

} /* namespace aro */

#endif /* CORE_CLONEABLE_IMPL_H */
