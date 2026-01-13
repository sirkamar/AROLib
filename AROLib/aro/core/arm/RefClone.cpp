#include <aro/core/impl/All.hpp>

/***********************************************************************
*                Ref<Cloneable<String>> Implementation                 *
***********************************************************************/

namespace aro {

//template <>
Ref<Cloneable<String>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Cloneable<String>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Cloneable<String>>::Ref(const char* chStr)
{
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<Cloneable<String>>::Ref(const wchar_t* chStr)
{
    ref = new String(chStr);

    if (ref != nullptr)
        Arm::add(ref, this);
}

//template <>
Ref<Cloneable<String>>::Ref(Ref<String>&& strRef) noexcept
{
   ref = strRef.ref;
   
   strRef.ref = nullptr;
}

//template <>
Ref<Cloneable<String>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Cloneable<String>>::Ref(const Ref<String>& strRef)
{
   ref = strRef.ref;

   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<Cloneable<String>>::Ref(Cloneable<String>* strPtr)
{
   if(strPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(!dynamic_cast<Object*>(strPtr))
   {
      RString str = typeid(*strPtr).name();
      
      throw RException(new CastException("Reference requires " + str + " be an Object-derived class"));
   }
   
   ref = strPtr;

   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<Cloneable<String>>::Ref(Ref<Cloneable<String>>&& strRef) noexcept
{
   ref = strRef.ref;

   strRef.ref = nullptr;
}

//template <>
Ref<Cloneable<String>>::Ref(const Ref<Cloneable<String>>& strRef)
{
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Cloneable<String>* Ref<Cloneable<String>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(const char* chStr)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(const wchar_t* chStr)
{
    if (ref != nullptr)
        Arm::remove(ref, this);

    ref = new String(chStr);

    if (ref != nullptr)
        Arm::add(ref, this);

    return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(Ref<String>&& strRef) noexcept
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strRef.ref;
   
   strRef.ref = nullptr;
   
   return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(const Ref<String>& strRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(Cloneable<String>* strPtr)
{
   if(strPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(!dynamic_cast<Object*>(strPtr))
   {
      RString str = typeid(*strPtr).name();
      
      throw RException(new CastException("Reference requires " + str + " be an Object-derived class"));
   }
   
   if(ref != nullptr)
      Arm::remove(ref, this);

   ref = strPtr;

   if(ref != nullptr)
      Arm::add(ref, this);

   return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(Ref<Cloneable<String>>&& strRef) noexcept
{
   if(this != &strRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);

      ref = strRef.ref;

      strRef.ref = nullptr;
   }

   return *this;
}

//template <>
Ref<Cloneable<String>>& Ref<Cloneable<String>>::operator=(const Ref<Cloneable<String>>& strRef)
{
   if(this != &strRef)
   {
      if(ref != nullptr)
         Arm::remove(ref, this);
      
      ref = strRef.ref;
      
      if(ref != nullptr)
         Arm::add(ref, this);
   }
   
   return *this;
}

//template <>
bool Ref<Cloneable<String>>::operator==(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) == objRef.ref;
}

//template <>
bool Ref<Cloneable<String>>::operator!=(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) != objRef.ref;
}

//template <>
Base* Ref<Cloneable<String>>::ptr() const
{
   return ref;
}

//template <>
void Ref<Cloneable<String>>::clear()
{
   ref = nullptr;
}

} /* namespace aro */
