#ifndef CORE_WEAKIMP_H
#define CORE_WEAKIMP_H

#include <aro/core/arm/RefIterator_.h>

namespace aro {

template <class T>
Weak<T>::Weak(const Ref<T>& aRef)
{
   ref = aRef.ref;
}

template <class T>
RString Weak<T>::toString()
{
   if(ref == nullptr)
      return getType() + "{null}";
   
   std::stringstream ss;
   
   ss << ref;
   
   return getType() + "{" + ss.str().c_str() + "}";
}

template <class T>
Ref<T> Weak<T>::get()
{
   if(ref != nullptr)
   {
      // check if object is still
      // alive within the ARM
      if(Arm::isAlive(ref))
	      return ref;
      
      ref = nullptr;
   }

   return nullref;
}

} /* namespace aro */

#endif /* CORE_WEAKIMP_H */
