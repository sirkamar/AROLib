#ifndef ARO_ARM_REFOBJECT_IMPL_H
#define ARO_ARM_REFOBJECT_IMPL_H

#include <aro/core/arm/RefTU-impl.h>
#include <aro/core/arm/RefObject.h>

namespace aro {

/************************************************************************
*               Ref<Object> Member Template Implementation              *
************************************************************************/

template <class T>
Ref<Object>::Ref(Ref<T>&& tRef)
{
   ref = dynamic_cast<Object*>(tRef.ref);
   
   tRef.ref = nullptr;
}

template <class T>
Ref<Object>::Ref(const Ref<T>& tRef)
{
   ref = dynamic_cast<Object*>(tRef.ref);
   
   if(ref != nullptr && !Arm::finalizing)
      Arm::add(ref, this);
}

template <class T>
Ref<Object>& Ref<Object>::operator=(Ref<T>&& tRef)
{
   if(ref != nullptr && !Arm::finalizing)
      Arm::remove(ref, this);
   
   ref = dynamic_cast<Object*>(tRef.ref);
   
   tRef.ref = nullptr;
   
   return *this;
}

template <class T>
Ref<Object>& Ref<Object>::operator=(const Ref<T>& tRef)
{
   if(ref != nullptr && !Arm::finalizing)
      Arm::remove(ref, this);
   
   ref = dynamic_cast<Object*>(tRef.ref);
   
   if(ref != nullptr && !Arm::finalizing)
      Arm::add(ref, this);
   
   return *this;
}

} /* namespace aro */

#endif /* ARO_ARM_REFOBJECT_IMPL_H */
