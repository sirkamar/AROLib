#include <aro/core/utils/Foreach.h>

/************************************************************************
*                      Ref< Object > Implementation                     *
************************************************************************/

namespace aro {

//template <>
Ref<Object>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Object>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Object>::Ref(Object* objPtr)
{
   if(objPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = objPtr;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<Object>::Ref(const char* chPtr)
{
   ref = new String(chPtr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

////template <>
//Ref<Object>::Ref(Ref<String>&& strRef)
//{
//   ref = strRef.ref;
//
//   strRef.ref = nullptr;
//}
//
////template <>
//Ref<Object>::Ref(const Ref<String>& strRef)
//{
//   ref = strRef.ref;
//
//   if(ref != nullptr)
//      Arm::add(ref, this);
//}

//template <>
Ref<Object>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Object>::Ref(Ref<Object>&& objRef)
{
   ref = objRef.ref;

   objRef.ref = nullptr;
}

//template <>
Ref<Object>::Ref(const Ref<Object>& objRef)
{
   ref = objRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Object* Ref<Object>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

//template <>
Ref<Object>& Ref<Object>::operator=(Object* objPtr)
{
   if(objPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = objPtr;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Object>& Ref<Object>::operator=(const char* chptr)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = new String(chptr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

////template <>
//Ref<Object>& Ref<Object>::operator=(Ref<String>&& strRef)
//{
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = strRef.ref;
//   
//   strRef.ref = nullptr;
//   
//   return *this;
//}
//
////template <>
//Ref<Object>& Ref<Object>::operator=(const Ref<String>& strRef)
//{
//   if(ref != nullptr)
//      Arm::remove(ref, this);
//   
//   ref = strRef.ref;
//   
//   if(ref != nullptr)
//      Arm::add(ref, this);
//   
//   return *this;
//}

//template <>
Ref<Object>& Ref<Object>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;

   return *this;
}

//template <>
Ref<Object>& Ref<Object>::operator=(Ref<Object>&& objRef)
{
   if (this != &objRef)
   {
      if (ref != nullptr)
         Arm::remove(ref, this);

      ref = objRef.ref;

      objRef.ref = nullptr;
   }

   return *this;
}

//template <>
Ref<Object>& Ref<Object>::operator=(const Ref<Object>& objRef)
{
   if(this != &objRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = objRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
bool Ref<Object>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<Object>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Base* Ref<Object>::ptr() const
{
   return ref;
}

//template <>
void Ref<Object>::clear()
{
   ref = nullptr;
}

} /* namespace aro */
