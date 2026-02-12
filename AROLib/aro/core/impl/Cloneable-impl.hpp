#ifndef CORE_CLONEABLE_IMPL_H
#define CORE_CLONEABLE_IMPL_H

#include <aro/core/impl/Weak-impl.hpp>
#include <aro/core/impl/ObjectFactory-impl.hpp>

namespace aro {

template <class T>
vbool Cloneable<T>::dummy = false;

template <class T>
Cloneable<T>::Cloneable()
{
   if (!dummy) {
      dummy = true;
      
      ObjectFactory::add(ObjectFactory::getTypeID<T>(), [](RObject obj) -> RObject {
         Ref<T> o_tmp = type_cast<T>(obj);

         return new T((*o_tmp.operator->()));
      });
   }
}

} /* namespace aro */

#endif /* CORE_CLONEABLE_IMPL_H */
