#ifndef ARO_ARM_REF_IMPL_H
#define ARO_ARM_REF_IMPL_H

#include <aro/core/arm/Ref.hpp>
#include <aro/core/arm/Arm.hpp>
#include <aro/core/Iterable.hpp>
#include <aro/core/CastException.hpp>
#include <aro/core/NullException.hpp>

namespace aro {

template <class U>
const Ref<U>& RefItr<U>::operator*() const
{
   return cur;
}

template <class U>
typename RefItr<U>& RefItr<U>::operator++()
{
   cur = list->hasNext() ? list->next() : nullref;

   return *this;
}

template <class U>
RefItr<U>::RefItr(const Ref<util::Iterator<U>>& lst)
   :list(lst)
{
   cur = (list != nullref && list->hasNext() ? list->next() : nullref);
}

template <class U>
bool RefItr<U>::operator!=(typename const RefItr<U>& itr) const
{
   return (cur != itr.cur || (list != nullref && list->hasNext()));
}

template <template <class> class T, class U>
typename RefItr<U> getRefItr(const Ref<T<U>>& itr)
{
   return class RefItr<U>(itr);
}


/************************************************************************
*                          Ref<T> Implementation                        *
************************************************************************/

template <class T>
Ref<T>::Ref()
{
   ref = nullptr;
}

template <class T>
Ref<T>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

template <class T>
Ref<T>::Ref(T* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(!dynamic_cast<Object*>(tPtr))
   {
      RString str = typeid(*tPtr).name();
      
      throw RException(new CastException("Reference requires "+str+" be an Object-derived class"));
   }
   
   ref = tPtr;
   
   Arm::add(ref, this);
}

template <class T>
Ref<T>::Ref(Ref<T>&& tRef) noexcept
{
   ref = tRef.ref;

   tRef.ref = nullptr;
}

template <class T> template <class U>
Ref<T>::Ref(Ref<U>&& uRef) noexcept
{
   ref = uRef.ref;

   uRef.ref = nullptr;
}

template <class T>
Ref<T>::Ref(const Ref<T>& tRef)
{
   ref = tRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

template <class T> template <class U>
Ref<T>::Ref(const Ref<U>& uRef)
{
   ref = uRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

template <class T>
Ref<T>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

template <class T>
T* Ref<T>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

template <class T>
Ref<T>& Ref<T>::operator=(T* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(!dynamic_cast<Object*>(tPtr))
   {
      RString str = typeid(*tPtr).name();
      
      throw RException(new CastException("Reference requires " +str+" to be an Object-derived class"));
   }
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = tPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(Ref<T>&& tRef) noexcept
{
   if(this != &tRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);

      ref = tRef.ref;

      tRef.ref = nullptr;
   }

   return *this;
}

template <class T> template <class U>
Ref<T>& Ref<T>::operator=(Ref<U>&& uRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = uRef.ref;
   
   uRef.ref = nullptr;

   return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(const Ref<T>& tRef)
{
   if(this != &tRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = tRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

template <class T> template <class U>
Ref<T>& Ref<T>::operator=(const Ref<U>& uRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
      
   ref = uRef.ref;
      
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

template <class T>
bool Ref<T>::operator==(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) == objRef.ref;
}

template <class T>
bool Ref<T>::operator!=(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) != objRef.ref;
}

template <class T>
Base* Ref<T>::ptr() const
{
   return ref;
}

template <class T>
void Ref<T>::clear()
{
   ref = nullptr;
}

template <class T> template <class U>
RefItr<U> Ref<T>::begin() const
{
   auto list = (*this)->iterator();
   
   return getRefItr(list);
}

template <class T> template <class U>
RefItr<U> Ref<T>::end() const
{
   auto list = (*this)->iterator();
   
   list = nullref;
   
   return getRefItr(list);
}

} /* namespace aro */

#endif /* ARO_ARM_REF_IMPL_H */
