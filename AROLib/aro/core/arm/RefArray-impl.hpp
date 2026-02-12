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
}

template <class T>
Ref<Array<T>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

template <class T>
Ref<Array<T>>::Ref(Ref<Array<T>>&& arrRef) noexcept
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

template <class T>
Ref<Array<T>>::Ref(const Ref<Array<T>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <class T> template <class U, typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type>
//Ref<Array<T>>::Ref(const Ref<Array<U>>& arrRef)
//{
//   if(arrRef.ref == nullptr)
//      ref = nullptr;
//   else
//   {
//      crossAssigned = true;
//      
//      class FilterArray : public ArrayBase<T,Ref<T>>
//      {
//         public:
//            FilterArray(Ref<Array<U>> arrRef)
//               :ArrayBase<T,Ref<T>>(arrRef->length), arrRef(arrRef)
//            {}
//
//            Ref<Object> clone()
//            {
//               return arrRef->clone();
//            }
//
//            Ref<String> toString()
//            {
//               return arrRef->toString();
//            }
//
//            void set(vint index, Ref<T> item)
//            {
//               arrRef->item(index) = type_cast<U>(item);
//            }
//
//            Ref<T> get(vint index)
//            {
//               return arrRef->item(index);
//            }
//
//            Ref<Array<T>> copyOf(vint count)
//            {
//               return copyOf(0, count);
//            }
//
//            Ref<Array<T>> copyOf(vint offset, vint count)
//            {
//               Ref<Array<T>> newArr = new Array<T>(count);
//               
//               for(vint i=0; i<count; i++)
//                  newArr->item(i) = arrRef->item(offset + i);
//               
//               return newArr;
//            }
//
//            void copy(vint dPos, Ref<Array<T>> src, vint sPos, vint num)
//            {
//               for(vint i=0; i<num; i++)
//                  arrRef->item(dPos + i) = type_cast<U>(src->item(sPos + i));
//            }
//
//            private:
//               Ref<Array<U>> arrRef;
//      };
//
//      RefArrayBase<T,Ref<T>>::ref = new FilterArray(arrRef);
//      
//      Arm::add(ref, this);
//   }
//}

template <class T>
Ref<Array<T>>::Ref(std::initializer_list<Ref<T>> elems)
{
   ref = new Array<T>(elems);

   Arm::add(ref, this);
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

//template <class T>
//Array<T>* Ref<Array<T>>::operator->() const
//{
//   if(ref == nullptr)
//      throw RException(new NullException());
//   
//   return ref;
//}

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
   if(crossAssigned && objRef.ref != nullptr)
   {
      Array<T>* arrPtr = dynamic_cast<Array<T>*>(objRef.ref);
      
      if(arrPtr != nullptr)
      {
         if(ref->length == arrPtr->length)
            return true;
         
         for(vint i = 0; i < ref->length; i++)
         {
            if(ref->get(i) == arrPtr->get(i))
               return true;
         }
         
         return false;
      }
   }

   return ref == objRef.ref;
}

template <class T>
bool Ref<Array<T>>::operator!=(const Ref<Object>& objRef) const
{
   if(crossAssigned && objRef.ref != nullptr)
   {
      Array<T>* arrPtr = dynamic_cast<Array<T>*>(objRef.ref);
      
      if(arrPtr != nullptr)
      {
         if(ref->length != arrPtr->length)
            return true;
         
         for(vint i = 0; i < ref->length; i++)
         {
            if(ref->get(i) != arrPtr->get(i))
               return true;
         }
         
         return false;
      }
   }
   
   return ref != objRef.ref;
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

//template <class T> template <class U, typename std::enable_if<std::is_convertible<U*, T*>::value, int>::type>
//Ref<Array<T>>& Ref<Array<T>>::operator=(const Ref<Array<U>>& arrRef)
//{
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   if(arrRef.ref == nullptr)
//   {
//      ref = nullptr;
//
//      crossAssigned = false;
//   }
//   else
//   {
//      crossAssigned = true;
//      
//      class FilterArray : public ArrayBase<T,Ref<T>>
//      {
//         public:
//            FilterArray(Ref<Array<U>> arrRef)
//               :ArrayBase<T,Ref<T>>(arrRef->length), arrRef(arrRef)
//            {}
//
//            Ref<Object> clone()
//            {
//               return arrRef->clone();
//            }
//
//            Ref<String> toString()
//            {
//               return arrRef->toString();
//            }
//
//            void set(vint index, Ref<T> item)
//            {
//               arrRef->item(index) = type_cast<U>(item);
//            }
//
//            Ref<T> get(vint index)
//            {
//               return arrRef->item(index);
//            }
//
//            Ref<Array<T>> copyOf(vint count)
//            {
//               return copyOf(0, count);
//            }
//
//            Ref<Array<T>> copyOf(vint offset, vint count)
//            {
//               Ref<Array<T>> newArr = new Array<T>(count);
//               
//               for(vint i=0; i<count; i++)
//                  newArr->item(i) = arrRef->item(offset + i);
//               
//               return newArr;
//            }
//
//            void copy(vint dPos, Ref<Array<T>> src, vint sPos, vint num)
//            {
//               for(vint i=0; i<num; i++)
//                  arrRef->item(dPos + i) = type_cast<U>(src->item(sPos + i));
//            }
//
//            private:
//               Ref<Array<U>> arrRef;
//      };
//
//      RefArrayBase<T,Ref<T>>::ref = new FilterArray(arrRef);
//      
//      Arm::add(ref, this);
//   }
//   
//   return *this;
//}

} /* namespace aro */

#endif /* ARO_ARM_ARRAYREF_IMPL_H */
