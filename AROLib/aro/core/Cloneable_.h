#ifndef CORE_CLONEABLE_IMP_H
#define CORE_CLONEABLE_IMP_H

//#include <aro/core/Cloneable.h>
#include <aro/core/utils/Class_.h>

namespace aro {

template <class T>
const Class<T> Cloneable<T>::CLONEID = 1;

template <class T>
Cloneable<T>::Cloneable()
{
   CLONEID.init();
}

} /* namespace aro */

#endif /* CORE_CLONEABLE_IMP_H */
