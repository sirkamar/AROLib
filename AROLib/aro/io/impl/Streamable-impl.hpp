#ifndef IO_STREAMABLE_IMPL_H
#define IO_STREAMABLE_IMPL_H

#include <aro/core/impl/Cloneable-impl.hpp>

namespace aro {

namespace io {

template <class T>
vbool Streamable<T>::dummy = false;

template <class T>
Streamable<T>::Streamable()
{
   if(!dummy) {
      dummy = true;
      
      ObjectFactory::add(ObjectFactory::getTypeID<T>(), []() -> RObject {
         return new T();
      });
   }
}

} /* namespace io */

} /* namespace aro */

#endif /* IO_STREAMABLE_IMPL_H */
