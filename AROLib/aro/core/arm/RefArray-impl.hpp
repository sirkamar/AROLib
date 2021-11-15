#ifndef ARO_ARM_ARRAYREF_IMPL_H
#define ARO_ARM_ARRAYREF_IMPL_H

#include <aro/core/arm/RefArray.hpp>
#include <aro/core/arm/RefArrayBase-impl.hpp>

namespace aro {

/**********************************************************************
*                      Ref<Array<T>> Implementation                   *
**********************************************************************/

template <class T>
Ref<Array<T>>::Ref()
{
   ref = nullptr;
   
   crossAssigned = false;
}

template <class T>
Ref<Array<T>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

template <class T>
Ref<Array<T>>::Ref(Array<T>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   crossAssigned = false;
}

template <class T>
Ref<Array<T>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
   
   crossAssigned = false;
}

template <class T>
Ref<Array<T>>::Ref(Ref<Array<T>>&& arrRef) noexcept
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
   
   crossAssigned = false;
}

template <class T>
Ref<Array<T>>::Ref(const Ref<Array<T>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   crossAssigned = false;
}

template <class T> template <class U>
Ref<Array<T>>::Ref(const Ref<Array<U>>& arrRef)
{
   if(arrRef.ref == nullptr)
   {
      ref = nullptr;
      
      crossAssigned = false;
   }
   else
   {
      ref = new Array<T>(arrRef->length);
      
      Arm::add(ref, this);
      
      crossAssigned = true;
      
      for(int n=0; n<ref->length; n++)
         ref->set(n, arrRef[n]);
   }
}

template <class T>
Ref<Array<T>>::Ref(std::initializer_list<Ref<T>> elems)
{
   ref = new Array<T>(elems);

   Arm::add(ref, this);
   
   crossAssigned = false;
}

template <class T>
void Ref<Array<T>>::clear()
{
   ref = nullptr;
   
   crossAssigned = false;
}

template <class T>
Base* Ref<Array<T>>::ptr() const
{
   return ref;
}

template <class T>
vint Ref<Array<T>>::size() const
{
   return (*this)->length;
}

template <class T>
Array<T>* Ref<Array<T>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return dynamic_cast<Array<T>*>(ref);
}

template <class T>
Ref<T>& Ref<Array<T>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref->item(index);
}

template <class T>
const Ref<T>& Ref<Array<T>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref->item(index);
}

template <class T>
bool Ref<Array<T>>::operator==(const Ref<Object>& objRef) const
{
   if(crossAssigned)
      return false;
   
   return ref == objRef.ref;
}

template <class T>
bool Ref<Array<T>>::operator!=(const Ref<Object>& objRef) const
{
   if(crossAssigned)
      return true;
   
   return ref != objRef.ref;
}

template <class T> template <class U>
bool Ref<Array<T>>::operator==(const Ref<Array<U>>& arrRef) const
{
   if(crossAssigned && arrRef.ref != nullptr && ref->length == arrRef->length)
   {
      for(int n=0; n<ref->length; n++)
         if(ref->item(n) != arrRef[n])
            return false;
      
      return true;
   }
   
   return false;
}

template <class T> template <class U>
bool Ref<Array<T>>::operator!=(const Ref<Array<U>>& arrRef) const
{
   if(crossAssigned && arrRef.ref != nullptr && ref->length == arrRef->length)
   {
      for(int n=0; n<ref->length; n++)
         if(ref->item(n) == arrRef[n])
            return false;
      
      return true;
   }
   
   return ref == nullptr ? arrRef.ref != nullptr : true;
}

template <class T>
Ref<Array<T>>& Ref<Array<T>>::operator=(Array<T>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   crossAssigned = false;
   
   return *this;
}

template <class T>
Ref<Array<T>>& Ref<Array<T>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   crossAssigned = false;
   
   return *this;
}

template <class T>
Ref<Array<T>>& Ref<Array<T>>::operator=(Ref<Array<T>>&& arrRef) noexcept
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
      
      crossAssigned = false;
   }
   
   return *this;
}

template <class T>
Ref<Array<T>>& Ref<Array<T>>::operator=(const Ref<Array<T>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
      
      crossAssigned = false;
   }
   
   return *this;
}

template <class T> template <class U>
Ref<Array<T>>& Ref<Array<T>>::operator=(const Ref<Array<U>>& arrRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   if(arrRef.ref == nullptr)
   {
      ref = nullptr;
      
      crossAssigned = false;
   }
   else
   {
      ref = new Array<T>(arrRef->length);
      
      Arm::add(ref, this);
      
      crossAssigned = true;

      for(int n=0; n<ref->length; n++)
         ref->set(n, arrRef[n]);
   }
   
   return *this;
}

} /* namespace aro */

#endif /* ARO_ARM_ARRAYREF_IMPL_H */
