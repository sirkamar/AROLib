#include <aro/core/utils/Foreach.hpp>

/************************************************************************
*               Ref<io::Streamable<String>> Implementation              *
************************************************************************/

namespace aro {

//template <>
Ref<io::Streamable<String>>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<io::Streamable<String>>::~Ref()
{
   if(ref != nullptr && !Arm::isFinalizing())
      Arm::remove(ref, this);
}

//template <>
Ref<io::Streamable<String>>::Ref(const char* chStr)
{
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<io::Streamable<String>>::Ref(const wchar_t* chStr)
{
    ref = new String(chStr);

    if (ref != nullptr)
        Arm::add(ref, this);
}

//template <>
Ref<io::Streamable<String>>::Ref(Ref<String>&& strRef) noexcept
{
   ref = strRef.ref;
   
   strRef.ref = nullptr;
}

//template <>
Ref<io::Streamable<String>>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<io::Streamable<String>>::Ref(const Ref<String>& strRef)
{
   ref = strRef.ref;

   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<io::Streamable<String>>::Ref(io::Streamable<String>* strPtr)
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
Ref<io::Streamable<String>>::Ref(Ref<io::Streamable<String>>&& strRef) noexcept
{
   ref = strRef.ref;

   strRef.ref = nullptr;
}

//template <>
Ref<io::Streamable<String>>::Ref(const Ref<io::Streamable<String>>& strRef)
{
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
io::Streamable<String>* Ref<io::Streamable<String>>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

//template <>
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(const char* chStr)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(const wchar_t* chStr)
{
    if (ref != nullptr)
        Arm::remove(ref, this);

    ref = new String(chStr);

    if (ref != nullptr)
        Arm::add(ref, this);

    return *this;
}

//template <>
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(Ref<String>&& strRef) noexcept
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strRef.ref;
   
   strRef.ref = nullptr;
   
   return *this;
}

//template <>
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(const Ref<String>& strRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(io::Streamable<String>* strPtr)
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
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(Ref<io::Streamable<String>>&& strRef) noexcept
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
Ref<io::Streamable<String>>& Ref<io::Streamable<String>>::operator=(const Ref<io::Streamable<String>>& strRef)
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
bool Ref<io::Streamable<String>>::operator==(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) == objRef.ref;
}

//template <>
bool Ref<io::Streamable<String>>::operator!=(const Ref<Object>& objRef) const
{
   return dynamic_cast<Object*>(ref) != objRef.ref;
}

//template <>
Base* Ref<io::Streamable<String>>::ptr() const
{
   return ref;
}

//template <>
void Ref<io::Streamable<String>>::clear()
{
   ref = nullptr;
}

} /* namespace aro */
