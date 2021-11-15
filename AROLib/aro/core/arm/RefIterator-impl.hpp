#ifndef ARO_ARM_REFITERATOR_IMPL_H
#define ARO_ARM_REFITERATOR_IMPL_H

#include <aro/core/arm/RefArray-impl.hpp>
#include <aro/core/arm/RefIterator.hpp>
#include <aro/util/Iterator.hpp>

namespace aro {

/************************************************************************
*                Ref<util::Iterator<T>> Implementation                  *
************************************************************************/

template <class T>
Ref<util::Iterator<T>>::Ref()
{
   ref = nullptr;
}

template <class T>
Ref<util::Iterator<T>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

template <class T>
Ref<util::Iterator<T>>::Ref(util::Iterator<T>* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));
   
   if(!dynamic_cast<Object*>(tPtr))
   {
      RString str = typeid(*tPtr).name();
      
      throw RException(new CastException("Reference requires "+str+" be an Object-derived class"));
   }
   
   ref = tPtr;
   
   Arm::add(ref, this);
}

template <class T>
Ref<util::Iterator<T>>::Ref(Ref<util::Iterator<T>>&& tRef)
{
   ref = tRef.ref;

   tRef.ref = nullptr;
}

template <class T> template <class U>
Ref<util::Iterator<T>>::Ref(Ref<U>&& uRef)
{
   ref = uRef.ref;

   uRef.ref = nullptr;
}

template <class T>
Ref<util::Iterator<T>>::Ref(const Ref<util::Iterator<T>>& tRef)
{
   ref = tRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

template <class T> template <class U>
Ref<util::Iterator<T>>::Ref(const Ref<U>& uRef)
{
   ref = uRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

template <class T>
Ref<util::Iterator<T>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

template <class T>
util::Iterator<T>* Ref<util::Iterator<T>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

template <class T>
Ref<util::Iterator<T>>& Ref<util::Iterator<T>>::operator=(util::Iterator<T>* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));
   
   if(!dynamic_cast<Object*>(tPtr))
   {
      RString str = typeid(*tPtr).name();
      
      throw RException(new CastException("Reference requires "+str+" be an Object-derived class"));
   }
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = tPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

template <class T>
Ref<util::Iterator<T>>& Ref<util::Iterator<T>>::operator=(Ref<util::Iterator<T>>&& tRef)
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
Ref<util::Iterator<T>>& Ref<util::Iterator<T>>::operator=(Ref<U>&& uRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = uRef.ref;
   
   uRef.ref = nullptr;

   return *this;
}

template <class T>
Ref<util::Iterator<T>>& Ref<util::Iterator<T>>::operator=(const Ref<util::Iterator<T>>& tRef)
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
Ref<util::Iterator<T>>& Ref<util::Iterator<T>>::operator=(const Ref<U>& uRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
      
   ref = uRef.ref;
      
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

template <class T>
Ref<util::Iterator<T>>& Ref<util::Iterator<T>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

template <class T>
bool Ref<util::Iterator<T>>::operator==(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) == objRef.ref;
}

template <class T>
bool Ref<util::Iterator<T>>::operator!=(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) != objRef.ref;
}

template <class T>
Base* Ref<util::Iterator<T>>::ptr() const
{
   return ref;
}

template <class T>
void Ref<util::Iterator<T>>::clear()
{
   ref = nullptr;
}


template <class T>
typename Ref<util::Iterator<T>>::Itr Ref<util::Iterator<T>>::begin() const
{
   return Itr(*this, true);
}

template <class T>
typename Ref<util::Iterator<T>>::Itr Ref<util::Iterator<T>>::end() const
{
   return Itr(*this, false);
}

template <class T>
Ref<T>* Ref<util::Iterator<T>>::Itr::operator->() const
{
   return cur.ref;
}

template <class T>
const Ref<T>& Ref<util::Iterator<T>>::Itr::operator*() const
{
   return cur;
}

template <class T>
typename Ref<util::Iterator<T>>::Itr& Ref<util::Iterator<T>>::Itr::operator++()
{
   if(list->hasNext())
      cur = list->next();
   else
      cur = nullref;

   return *this;
}

template <class T>
Ref<util::Iterator<T>>::Itr::Itr(const Ref<util::Iterator<T>>& lst, bool start)
   :list(lst)
{
   cur = start && list->hasNext() ? list->next() : nullref;
}

template <class T>
bool Ref<util::Iterator<T>>::Itr::operator!=(typename const Ref<util::Iterator<T>>::Itr& itr) const
{
   return (list.ref != itr.list.ref || cur != itr.cur);
}


} /* namespace aro */

#endif /* ARO_ARM_REFITERATOR_IMPL_H */
