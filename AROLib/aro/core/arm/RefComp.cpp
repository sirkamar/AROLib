#include <aro/core/impl/All.hpp>

/**********************************************************************
*              Ref<Comparable<String>> Implementation                 *
**********************************************************************/

namespace aro {

//template <>
Ref<Comparable<String>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<Comparable<String>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<Comparable<String>>::Ref(const char* chStr)
{
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<Comparable<String>>::Ref(const wchar_t* chStr)
{
    ref = new String(chStr);

    if (ref != nullptr)
        Arm::add(ref, this);
}

//template <>
Ref<Comparable<String>>::Ref(Ref<String>&& strRef) noexcept
{
   ref = strRef.ref;

   strRef.ref = nullptr;
}

//template <>
Ref<Comparable<String>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<Comparable<String>>::Ref(const Ref<String>& strRef)
{
   ref = strRef.ref;

   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<Comparable<String>>::Ref(Comparable<String>* strPtr)
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
Ref<Comparable<String>>::Ref(Ref<Comparable<String>>&& strRef) noexcept
{
   ref = strRef.ref;

   strRef.ref = nullptr;
}

//template <>
Ref<Comparable<String>>::Ref(const Ref<Comparable<String>>& strRef)
{
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Comparable<String>* Ref<Comparable<String>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

//template <>
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(const char* chStr)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(const wchar_t* chStr)
{
    if (ref != nullptr)
        Arm::remove(ref, this);

    ref = new String(chStr);

    if (ref != nullptr)
        Arm::add(ref, this);

    return *this;
}

//template <>
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(Ref<String>&& strRef) noexcept
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strRef.ref;
   
   strRef.ref = nullptr;
   
   return *this;
}

//template <>
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(const Ref<String>& strRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(Comparable<String>* strPtr)
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
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(Ref<Comparable<String>>&& strRef) noexcept
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
Ref<Comparable<String>>& Ref<Comparable<String>>::operator=(const Ref<Comparable<String>>& strRef)
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
bool Ref<Comparable<String>>::operator==(const Ref<Object>& objRef) const
{
   return Ref<Object>(*this) == objRef;
}

//template <>
bool Ref<Comparable<String>>::operator!=(const Ref<Object>& objRef) const
{
   return Ref<Object>(*this) != objRef;
}

//template <>
Base* Ref<Comparable<String>>::ptr() const
{
   return ref;
}

//template <>
void Ref<Comparable<String>>::clear()
{
   ref = nullptr;
}

} /* namespace aro */
