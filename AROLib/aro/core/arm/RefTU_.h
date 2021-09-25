#ifndef ARM_REFTU_IMP_H
#define ARM_REFTU_IMP_H

#include <aro/core/arm/Ref_.h>
#include <aro/core/arm/RefTU.h>
#include <aro/core/Iterable.h>

namespace aro {

/************************************************************************
*                         Ref<T<U>> Implementation                      *
************************************************************************/

template <template <typename> class T, class U>
Ref<T<U>>::Ref()
{
   ref = nullptr;
}

template <template <typename> class T, class U>
Ref<T<U>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

template <template <typename> class T, class U>
Ref<T<U>>::Ref(T<U>* tPtr)
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

template <template <typename> class T, class U>
Ref<T<U>>::Ref(Ref<T<U>>&& tRef)
{
   ref = tRef.ref;

   tRef.ref = nullptr;
}

//template <template <typename> class T, class U> template <template <typename> class V>
//Ref<T<U>>::Ref(Ref<V<U>>&& vRef)
//{
//   ref = vRef.ref;
//   
//   vRef.ref = nullptr;
//}

template <template <typename> class T, class U>
Ref<T<U>>::Ref(const Ref<T<U>>& tRef)
{
   ref = tRef.ref;

   if(ref != nullptr)
      Arm::add(ref, this);
}

template <template <typename> class T, class U> template <class V>
Ref<T<U>>::Ref(const Ref<V>& tRef)
{
   ref = tRef.ref;

   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <template <typename> class T, class U> template <template <typename> class V>
//Ref<T<U>>::Ref(const Ref<V<U>>& vRef)
//{
//   ref = vRef.ref;
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//}

template <template <typename> class T, class U>
Ref<T<U>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

template <template <typename> class T, class U>
T<U>* Ref<T<U>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

template <template <typename> class T, class U>
Ref<T<U>>& Ref<T<U>>::operator=(T<U>* tPtr)
{
   if(tPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));

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

template <template <typename> class T, class U> template <class V>
Ref<T<U>>& Ref<T<U>>::operator=(const Ref<V>& vRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = vRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

template <template <typename> class T, class U>
Ref<T<U>>& Ref<T<U>>::operator=(Ref<T<U>>&& tRef)
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

//template <template <typename> class T, class U> template <class V>
//Ref<T<U>>& Ref<T<U>>::operator=(Ref<T<V>>&& uRef)
//{
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//
//   ref = uRef.ref;
//
//   uRef.ref = nullptr;
//
//   return *this;
//}

template <template <typename> class T, class U>
Ref<T<U>>& Ref<T<U>>::operator=(const Ref<T<U>>& tRef)
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

//template <template <typename> class T, class U> template <class V>
//Ref<T<U>>& Ref<T<U>>::operator=(const Ref<T<V>>& uRef)
//{
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//
//   ref = uRef.ref;
//
//   if(ref != nullptr)
//      Arm::add(ref, this);
//
//   return *this;
//}

template <template <typename> class T, class U>
Ref<T<U>>& Ref<T<U>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);

   ref = nullptr;

   return *this;
}

template <template <typename> class T, class U>
bool Ref<T<U>>::operator==(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) == objRef.ref;
}

template <template <typename> class T, class U>
bool Ref<T<U>>::operator!=(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) != objRef.ref;
}

template <template <typename> class T, class U>
Base* Ref<T<U>>::ptr() const
{
   return ref;
}

template <template <typename> class T, class U>
void Ref<T<U>>::clear()
{
   ref = nullptr;
}

template <template <typename> class T, class U>
typename Ref<T<U>>::Itr Ref<T<U>>::begin() const
{
   Ref<Iterable<U>> list = *this;
   
   return Itr(list->iterator());
}

template <template <typename> class T, class U>
typename Ref<T<U>>::Itr Ref<T<U>>::end() const
{
   return Itr(nullref);
}

template <template <typename> class T, class U>
const Ref<U>& Ref<T<U>>::Itr::operator*() const
{
   return cur;
}

template <template <typename> class T, class U>
typename Ref<T<U>>::Itr& Ref<T<U>>::Itr::operator++()
{
   cur = list->hasNext() ? list->next() : nullref;
   
   return *this;
}

template <template <typename> class T, class U>
Ref<T<U>>::Itr::Itr(const Ref<util::Iterator<U>>& lst)
   :list(lst)
{
   cur = list.ref != nullptr && list->hasNext() ? list->next() : nullref;
}

template <template <typename> class T, class U>
bool Ref<T<U>>::Itr::operator!=(typename const Ref<T<U>>::Itr& itr) const
{
   return (cur != itr.cur || (list.ref != nullptr && list->hasNext()));
}

} /* namespace aro */

#endif // !ARM_REFTU_IMP_H

