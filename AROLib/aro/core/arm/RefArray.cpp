#include <aro/core/utils/Foreach.h>

namespace aro {

/************************************************************************
*                      Ref<Array<vint>> Implementation                  *
************************************************************************/

//template <>
Ref<Array<vint>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vint>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vint>>::Ref(Array<vint>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vint>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vint>>::Ref(Ref<Array<vint>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vint>>::Ref(const Ref<Array<vint>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vint>>::Ref(const Ref<Array<T>>& arrRef)
//   :RefArrayBase<vint>(arrPtr)
//{
//   T ur; vint tr = ur; // ensure T is assignable to vint
//   
//   ref = reinterpret_cast<Array<vint>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//}

//template <>
Ref<Array<vint>>::Ref(std::initializer_list<vint> elems)
{
   ref = new Array<vint>(elems);

   Arm::add(ref, this);
}

//template <>
const vint& Ref<Array<vint>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref->item(index);
}

//template <>
vint& Ref<Array<vint>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref->item(index);
}

//template <>
void Ref<Array<vint>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vint>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vint>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vint>* Ref<Array<vint>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vint>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vint>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vint>>& Ref<Array<vint>>::operator=(Array<vint>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vint>>& Ref<Array<vint>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vint>>& Ref<Array<vint>>::operator=(Ref<Array<vint>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vint>>& Ref<Array<vint>>::operator=(const Ref<Array<vint>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vint>>& Ref<Array<vint>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vint tr = t; // ensure T is assignable to vint
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vint>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}



/************************************************************************
*                      Ref<Array<vbool>> Implementation                 *
************************************************************************/

//template <>
Ref<Array<vbool>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vbool>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vbool>>::Ref(Array<vbool>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vbool>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vbool>>::Ref(Ref<Array<vbool>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vbool>>::Ref(const Ref<Array<vbool>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vbool>>::Ref(const Ref<Array<T>>& arrRef)
//{
//   
//}

//template <>
Ref<Array<vbool>>::Ref(std::initializer_list<vbool> elems)
{
   ref = new Array<vbool>(elems);

   Arm::add(ref, this);
}

//template <>
const vbool& Ref<Array<vbool>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
vbool& Ref<Array<vbool>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
void Ref<Array<vbool>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vbool>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vbool>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vbool>* Ref<Array<vbool>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vbool>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vbool>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vbool>>& Ref<Array<vbool>>::operator=(Array<vbool>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vbool>>& Ref<Array<vbool>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vbool>>& Ref<Array<vbool>>::operator=(Ref<Array<vbool>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vbool>>& Ref<Array<vbool>>::operator=(const Ref<Array<vbool>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vbool>>& Ref<Array<vbool>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vbool tr = t; // ensure T is assignable to vbool
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vbool>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}


/************************************************************************
*                      Ref<Array<vchar>> Implementation                 *
************************************************************************/

//template <>
Ref<Array<vchar>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vchar>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vchar>>::Ref(Array<vchar>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vchar>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vchar>>::Ref(Ref<Array<vchar>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vchar>>::Ref(const Ref<Array<vchar>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vchar>>::Ref(const Ref<Array<T>>& arrRef)
//{
//   
//}

//template <>
Ref<Array<vchar>>::Ref(std::initializer_list<vchar> elems)
{
   ref = new Array<vchar>(elems);

   Arm::add(ref, this);
}

//template <>
const vchar& Ref<Array<vchar>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
vchar& Ref<Array<vchar>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
void Ref<Array<vchar>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vchar>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vchar>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vchar>* Ref<Array<vchar>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vchar>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vchar>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vchar>>& Ref<Array<vchar>>::operator=(Array<vchar>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vchar>>& Ref<Array<vchar>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vchar>>& Ref<Array<vchar>>::operator=(Ref<Array<vchar>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vchar>>& Ref<Array<vchar>>::operator=(const Ref<Array<vchar>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vchar>>& Ref<Array<vchar>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vchar tr = t; // ensure T is assignable to vchar
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vchar>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}


/************************************************************************
*                      Ref<Array<vlong>> Implementation                 *
************************************************************************/

//template <>
Ref<Array<vlong>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vlong>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vlong>>::Ref(Array<vlong>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vlong>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vlong>>::Ref(Ref<Array<vlong>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vlong>>::Ref(const Ref<Array<vlong>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vlong>>::Ref(const Ref<Array<T>>& arrRef)
//{
//   
//}

//template <>
Ref<Array<vlong>>::Ref(std::initializer_list<vlong> elems)
{
   ref = new Array<vlong>(elems);

   Arm::add(ref, this);
}

//template <>
const vlong& Ref<Array<vlong>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
vlong& Ref<Array<vlong>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
void Ref<Array<vlong>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vlong>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vlong>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vlong>* Ref<Array<vlong>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vlong>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vlong>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vlong>>& Ref<Array<vlong>>::operator=(Array<vlong>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vlong>>& Ref<Array<vlong>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vlong>>& Ref<Array<vlong>>::operator=(Ref<Array<vlong>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vlong>>& Ref<Array<vlong>>::operator=(const Ref<Array<vlong>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vlong>>& Ref<Array<vlong>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vlong tr = t; // ensure T is assignable to vlong
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vlong>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}


/************************************************************************
*                    Ref<Array<vshort>> Implementation                  *
************************************************************************/

//template <>
Ref<Array<vshort>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vshort>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vshort>>::Ref(Array<vshort>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vshort>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vshort>>::Ref(Ref<Array<vshort>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vshort>>::Ref(const Ref<Array<vshort>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vshort>>::Ref(const Ref<Array<T>>& arrRef)
//{
//   
//}

//template <>
Ref<Array<vshort>>::Ref(std::initializer_list<vshort> elems)
{
   ref = new Array<vshort>(elems);

   Arm::add(ref, this);
}

//template <>
const vshort& Ref<Array<vshort>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
vshort& Ref<Array<vshort>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
void Ref<Array<vshort>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vshort>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vshort>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vshort>* Ref<Array<vshort>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vshort>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vshort>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vshort>>& Ref<Array<vshort>>::operator=(Array<vshort>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vshort>>& Ref<Array<vshort>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vshort>>& Ref<Array<vshort>>::operator=(Ref<Array<vshort>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vshort>>& Ref<Array<vshort>>::operator=(const Ref<Array<vshort>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vshort>>& Ref<Array<vshort>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vshort tr = t; // ensure T is assignable to vshort
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vshort>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}


/************************************************************************
*                     Ref<Array<vfloat>> Implementation                 *
************************************************************************/

//template <>
Ref<Array<vfloat>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vfloat>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vfloat>>::Ref(Array<vfloat>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vfloat>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vfloat>>::Ref(Ref<Array<vfloat>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vfloat>>::Ref(const Ref<Array<vfloat>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vfloat>>::Ref(const Ref<Array<T>>& arrRef)
//{
//   
//}

//template <>
Ref<Array<vfloat>>::Ref(std::initializer_list<vfloat> elems)
{
   ref = new Array<vfloat>(elems);

   Arm::add(ref, this);
}

//template <>
const vfloat& Ref<Array<vfloat>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
vfloat& Ref<Array<vfloat>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
void Ref<Array<vfloat>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vfloat>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vfloat>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vfloat>* Ref<Array<vfloat>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vfloat>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vfloat>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vfloat>>& Ref<Array<vfloat>>::operator=(Array<vfloat>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vfloat>>& Ref<Array<vfloat>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vfloat>>& Ref<Array<vfloat>>::operator=(Ref<Array<vfloat>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vfloat>>& Ref<Array<vfloat>>::operator=(const Ref<Array<vfloat>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vfloat>>& Ref<Array<vfloat>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vfloat tr = t; // ensure T is assignable to vfloat
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vfloat>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}


/************************************************************************
*                    Ref<Array<vdouble>> Implementation                 *
************************************************************************/

//template <>
Ref<Array<vdouble>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Array<vdouble>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Array<vdouble>>::Ref(Array<vdouble>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = arrPtr;
   
   Arm::add(ref, this);
}

//template <>
Ref<Array<vdouble>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Array<vdouble>>::Ref(Ref<Array<vdouble>>&& arrRef)
{
   ref = arrRef.ref;
   
   arrRef.ref = nullptr;
}

//template <>
Ref<Array<vdouble>>::Ref(const Ref<Array<vdouble>>& arrRef)
{
   ref = arrRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template<>
//template <class T>
//Ref<Array<vdouble>>::Ref(const Ref<Array<T>>& arrRef)
//{
//   
//}

//template <>
Ref<Array<vdouble>>::Ref(std::initializer_list<vdouble> elems)
{
   ref = new Array<vdouble>(elems);

   Arm::add(ref, this);
}

//template <>
const vdouble& Ref<Array<vdouble>>::operator[](int index) const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
vdouble& Ref<Array<vdouble>>::operator[](int index)
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref->item(index);
}

//template <>
void Ref<Array<vdouble>>::clear()
{
   ref = nullptr;
}

//template <>
Base* Ref<Array<vdouble>>::ptr() const
{
   return ref;
}

//template <>
vint Ref<Array<vdouble>>::size() const
{
   return (*this)->length;
}

//template <>
Array<vdouble>* Ref<Array<vdouble>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
bool Ref<Array<vdouble>>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Array<vdouble>>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<Array<vdouble>>& Ref<Array<vdouble>>::operator=(Array<vdouble>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = arrPtr;
   
   Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Array<vdouble>>& Ref<Array<vdouble>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Array<vdouble>>& Ref<Array<vdouble>>::operator=(Ref<Array<vdouble>>&& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      arrRef.ref = nullptr;
   }
   
   return *this;
}

//template <>
Ref<Array<vdouble>>& Ref<Array<vdouble>>::operator=(const Ref<Array<vdouble>>& arrRef)
{
   if(this != &arrRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = arrRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
//template <class T>
//Ref<Array<vdouble>>& Ref<Array<vdouble>>::operator=(const Ref<Array<T>>& arrRef)
//{
//   T t; vdouble tr = t; // ensure T is assignable to vdouble
//   
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = reinterpret_cast<Array<vdouble>*>(arrRef.ref);
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}

} /* namespace aro */
