#include <aro/core/Array2D_.h>

namespace aro {

/**********************************************************************
*                   RefArrayBase<vint> Implementation                    *
**********************************************************************/

//template <>
RefArrayBase<vint>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vint>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vint>::RefArrayBase(Array<vint>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vint>::RefArrayBase(RefArrayBase<vint>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vint>::RefArrayBase(const RefArrayBase<vint>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vint>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vint>* RefArrayBase<vint>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

//template <>
typename RefArrayBase<vint>::Itr RefArrayBase<vint>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vint>::Itr RefArrayBase<vint>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vint>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vint>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vint& RefArrayBase<vint>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vint>::Itr& RefArrayBase<vint>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;
   
   return *this;
}

//template <>
RefArrayBase<vint>::Itr::Itr(const RefArrayBase<vint>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vint>::Itr::operator!=(typename const RefArrayBase<vint>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}

/**********************************************************************
*                   RefArrayBase<vbool> Implementation                    *
**********************************************************************/
//template <>
RefArrayBase<vbool>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vbool>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vbool>::RefArrayBase(Array<vbool>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vbool>::RefArrayBase(RefArrayBase<vbool>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vbool>::RefArrayBase(const RefArrayBase<vbool>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vbool>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vbool>* RefArrayBase<vbool>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
typename RefArrayBase<vbool>::Itr RefArrayBase<vbool>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vbool>::Itr RefArrayBase<vbool>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vbool>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vbool>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vbool& RefArrayBase<vbool>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vbool>::Itr& RefArrayBase<vbool>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;

   return *this;
}

//template <>
RefArrayBase<vbool>::Itr::Itr(const RefArrayBase<vbool>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vbool>::Itr::operator!=(typename const RefArrayBase<vbool>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}

/**********************************************************************
*                   RefArrayBase<vchar> Implementation                    *
**********************************************************************/
//template <>
RefArrayBase<vchar>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vchar>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vchar>::RefArrayBase(Array<vchar>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vchar>::RefArrayBase(RefArrayBase<vchar>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vchar>::RefArrayBase(const RefArrayBase<vchar>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vchar>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vchar>* RefArrayBase<vchar>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
typename RefArrayBase<vchar>::Itr RefArrayBase<vchar>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vchar>::Itr RefArrayBase<vchar>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vchar>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vchar>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vchar& RefArrayBase<vchar>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vchar>::Itr& RefArrayBase<vchar>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;

   return *this;
}

//template <>
RefArrayBase<vchar>::Itr::Itr(const RefArrayBase<vchar>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vchar>::Itr::operator!=(typename const RefArrayBase<vchar>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}


/**********************************************************************
*                   RefArrayBase<vlong> Implementation                    *
**********************************************************************/
//template <>
RefArrayBase<vlong>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vlong>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vlong>::RefArrayBase(Array<vlong>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vlong>::RefArrayBase(RefArrayBase<vlong>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vlong>::RefArrayBase(const RefArrayBase<vlong>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vlong>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vlong>* RefArrayBase<vlong>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
typename RefArrayBase<vlong>::Itr RefArrayBase<vlong>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vlong>::Itr RefArrayBase<vlong>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vlong>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vlong>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vlong& RefArrayBase<vlong>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vlong>::Itr& RefArrayBase<vlong>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;

   return *this;
}

//template <>
RefArrayBase<vlong>::Itr::Itr(const RefArrayBase<vlong>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vlong>::Itr::operator!=(typename const RefArrayBase<vlong>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}


/**********************************************************************
*                   RefArrayBase<vshort> Implementation                    *
**********************************************************************/
//template <>
RefArrayBase<vshort>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vshort>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vshort>::RefArrayBase(Array<vshort>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vshort>::RefArrayBase(RefArrayBase<vshort>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vshort>::RefArrayBase(const RefArrayBase<vshort>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vshort>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vshort>* RefArrayBase<vshort>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
typename RefArrayBase<vshort>::Itr RefArrayBase<vshort>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vshort>::Itr RefArrayBase<vshort>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vshort>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vshort>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vshort& RefArrayBase<vshort>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vshort>::Itr& RefArrayBase<vshort>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;

   return *this;
}

//template <>
RefArrayBase<vshort>::Itr::Itr(const RefArrayBase<vshort>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vshort>::Itr::operator!=(typename const RefArrayBase<vshort>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}


/**********************************************************************
*                   RefArrayBase<vfloat> Implementation                    *
**********************************************************************/
//template <>
RefArrayBase<vfloat>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vfloat>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vfloat>::RefArrayBase(Array<vfloat>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vfloat>::RefArrayBase(RefArrayBase<vfloat>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vfloat>::RefArrayBase(const RefArrayBase<vfloat>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vfloat>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vfloat>* RefArrayBase<vfloat>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
typename RefArrayBase<vfloat>::Itr RefArrayBase<vfloat>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vfloat>::Itr RefArrayBase<vfloat>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vfloat>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vfloat>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vfloat& RefArrayBase<vfloat>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vfloat>::Itr& RefArrayBase<vfloat>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;

   return *this;
}

//template <>
RefArrayBase<vfloat>::Itr::Itr(const RefArrayBase<vfloat>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vfloat>::Itr::operator!=(typename const RefArrayBase<vfloat>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}


/**********************************************************************
*                   RefArrayBase<vdouble> Implementation                    *
**********************************************************************/
//template <>
RefArrayBase<vdouble>::RefArrayBase()
{
   ref = nullptr;
}

//template <>
RefArrayBase<vdouble>::~RefArrayBase()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref);
}

//template <>
RefArrayBase<vdouble>::RefArrayBase(Array<vdouble>* arrPtr)
{
   if(arrPtr == nullptr)
      throw RException(new NullException("Illegal null pointer initialization"));

   ref = arrPtr;

   Arm::add(ref);
}

//template <>
RefArrayBase<vdouble>::RefArrayBase(RefArrayBase<vdouble>&& arrRef)
{
   ref = arrRef.ref;

   arrRef.ref = nullptr;
}

//template <>
RefArrayBase<vdouble>::RefArrayBase(const RefArrayBase<vdouble>& arrRef)
{
   ref = arrRef.ref;

   if(ref != nullptr)
      Arm::add(ref);
}

////template <> template <class U>
//RefArrayBase<vdouble>::RefArrayBase(const RefArrayBase<U>& arrRef)
//{
//   
//}

//template <>
Array<vdouble>* RefArrayBase<vdouble>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());

   return ref;
}

//template <>
typename RefArrayBase<vdouble>::Itr RefArrayBase<vdouble>::end() const
{
   return Itr(*this, (*this)->length);
}

//template <>
typename RefArrayBase<vdouble>::Itr RefArrayBase<vdouble>::begin() const
{
   return Itr(*this, 0);
}

//template <>
bool RefArrayBase<vdouble>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool RefArrayBase<vdouble>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
const vdouble& RefArrayBase<vdouble>::Itr::operator*() const
{
   return arr[pos];
}

//template <>
typename RefArrayBase<vdouble>::Itr& RefArrayBase<vdouble>::Itr::operator++()
{
   if(pos < arr->length)
      pos++;

   return *this;
}

//template <>
RefArrayBase<vdouble>::Itr::Itr(const RefArrayBase<vdouble>& ra, int p)
   :arr(ra)
{
   pos = p;
}

//template <>
bool RefArrayBase<vdouble>::Itr::operator!=(typename const RefArrayBase<vdouble>::Itr& itr) const
{
   return (arr.ref != itr.arr.ref || pos != itr.pos);
}


} /* namespace aro */
