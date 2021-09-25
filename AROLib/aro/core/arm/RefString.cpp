#include <aro/core/utils/Foreach.h>

/************************************************************************
*                        Ref<String> Implementation                     *
************************************************************************/

namespace aro {

//template <>
Ref<String>::Ref()
{
   ref = nullptr;
}

//template <>
Ref<String>::~Ref()
{
   if(ref != nullptr && !Arm::finalizing)
      Arm::remove(ref, this);
}

//template <>
Ref<String>::Ref(String* strPtr)
{
   if(strPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   ref = strPtr;
   
   if(ref != nullptr && !Arm::finalizing)
      Arm::add(ref, this);
}

//template <>
Ref<String>::Ref(const char* chStr)
{
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<String>::Ref(const wchar_t* chStr)
{
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
Ref<String>::Ref(Ref<String>&& strRef)
{
   ref = strRef.ref;

   strRef.ref = nullptr;
}

//template <>
Ref<String>::Ref(const Ref<Null>& nRef)
{
   ref = nullptr;
}

//template <>
Ref<String>::Ref(const Ref<String>& strRef)
{
   ref = strRef.ref;
   
   if(ref != nullptr)
      Arm::add(ref, this);
}

//template <>
String* Ref<String>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

Ref<String>::operator const wchar_t*() const
{
   if(ref != nullptr)
      return ref->toCString();
   
   return nullptr;
}

//template <>
bool Ref<String>::operator==(const Ref<Object>& objRef) const
{
   return ref == objRef.ref;
}

//template <>
bool Ref<String>::operator!=(const Ref<Object>& objRef) const
{
   return ref != objRef.ref;
}

//template <>
Ref<String>& Ref<String>::operator=(String* strPtr)
{
   if(strPtr == nullptr)
      throw RException(new NullException("Reference null pointer initialization"));
   
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = strPtr;
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<String>& Ref<String>::operator=(const char* chStr)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = new String(chStr);
   
   if(ref != nullptr)
      Arm::add(ref, this);
   
   return *this;
}

//template <>
Ref<String>& Ref<String>::operator=(const wchar_t* chStr)
{
   if(ref != nullptr)
      Arm::remove(ref, this);

   ref = new String(chStr);

   if(ref != nullptr)
      Arm::add(ref, this);

   return *this;
}

//template <>
Ref<String>& Ref<String>::operator=(Ref<String>&& strRef)
{
   if (this != &strRef)
   {
      if (ref != nullptr)
         Arm::remove(ref, this);

      ref = strRef.ref;

      strRef.ref = nullptr;
   }

   return *this;
}

//template <>
Ref<String>& Ref<String>::operator=(const Ref<Null>& nRef)
{
   if(ref != nullptr)
      Arm::remove(ref, this);
   
   ref = nullptr;
   
   return *this;
}

//template <>
Ref<String>& Ref<String>::operator=(const Ref<String>& strRef)
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
Base* Ref<String>::ptr() const
{
   return ref;
}

//template <>
void Ref<String>::clear()
{
   ref = nullptr;
}

//template <>
Ref<String>& Ref<String>::operator+=(const Ref<Object>& objRef)
{
   return (*this) = (*this) + objRef;
}

//template <>
Ref<String> Ref<String>::operator+(const char* chStr) const
{
   return String::valueOf(*this)->concat(chStr);
}

//template <>
Ref<String> Ref<String>::operator+(const wchar_t* chStr) const
{
   return String::valueOf(*this)->concat(chStr);
}

//template <>
Ref<String> Ref<String>::operator+(const Ref<Object>& objRef) const
{
   return String::valueOf(*this)->concat(String::valueOf(objRef));
}

//template <>
Ref<String> Ref<String>::operator+(const Ref<String>& strRef) const
{
   return String::valueOf(*this)->concat(String::valueOf(strRef));
}

Ref<String> operator+(const char* chStr, const Ref<Object>& objRef)
{
   return Ref<String>(chStr)->concat(String::valueOf(objRef));
}

Ref<String> operator+(const char* chStr, const Ref<String>& strRef)
{
   return Ref<String>(chStr)->concat(String::valueOf(RObject(strRef)));
}

Ref<String> operator+(const Ref<Object>& objRef, const char* chStr)
{
   return String::valueOf(objRef)->concat(chStr);
}

Ref<String> operator+(const wchar_t* chStr, const Ref<Object>& objRef)
{
   return Ref<String>(chStr)->concat(String::valueOf(objRef));
}

Ref<String> operator+(const wchar_t* chStr, const Ref<String>& strRef)
{
   return Ref<String>(chStr)->concat(String::valueOf(RObject(strRef)));
}

Ref<String> operator+(const Ref<Object>& objRef, const wchar_t* chStr)
{
   return String::valueOf(objRef)->concat(chStr);
}

Ref<String> operator+(const Ref<Object>& objRef, const Ref<String>& strRef)
{
   return String::valueOf(objRef)->concat(String::valueOf(strRef));
}

} /* namespace aro */
