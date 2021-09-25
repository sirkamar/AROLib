#ifndef ARO_ARM_REFWEAKIMP_H
#define ARO_ARM_REFWEAKIMP_H

#include <aro/core/arm/RefObject_.h>
#include <aro/core/arm/RefWeak.h>
#include <aro/core/Weak.h>

namespace aro {

template <class T>
Ref<Weak<T>>::Ref()
{
   ref = nullptr;
}

template <class T>
Ref<Weak<T>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

template <class T>
Ref<Weak<T>>::Ref(Weak<T>* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = tPtr;
   
   Arm::add(ref, this);
}

template <class T>
Ref<Weak<T>>::Ref(const Ref<T> &tRef)
{
   ref = new Weak<T>(tRef);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

template <class T>
Ref<Weak<T>>::Ref(Ref<Weak<T>>&& tRef)
{
   ref = tRef.ref;

   tRef.ref = nullptr;
}

template <class T>
Ref<Weak<T>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

template <class T>
Ref<Weak<T>>::Ref(const Ref<Weak<T>>& tRef)
{
   ref = tRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

template <class T>
Weak<T>* Ref<Weak<T>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

template <class T>
Ref<Weak<T>>& Ref<Weak<T>>::operator=(Weak<T>* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = tPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

template <class T>
Ref<Weak<T>>& Ref<Weak<T>>::operator=(const Ref<T>& tRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = new Weak<T>(tRef);
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

template <class T>
Ref<Weak<T>>& Ref<Weak<T>>::operator=(Ref<Weak<T>>&& wRef)
{
   if (this != &wRef)
   {
      if (ref != nullptr)
         Arm::remove(ref, this);

      ref = wRef.ref;

      wRef.ref = nullptr;
   }

   return *this;
}

template <class T>
Ref<Weak<T>>& Ref<Weak<T>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

template <class T>
Ref<Weak<T>>& Ref<Weak<T>>::operator=(const Ref<Weak<T>>& wRef)
{
   if(this != &wRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = wRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

template <class T>
bool Ref<Weak<T>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

template <class T>
bool Ref<Weak<T>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

template <class T>
Base* Ref<Weak<T>>::ptr() const
{
   return ref;
}

template <class T>
void Ref<Weak<T>>::clear()
{
   ref = nullptr;
}

} /* namespace aro */

#endif /* ARO_ARM_REFWEAKIMP_H */
