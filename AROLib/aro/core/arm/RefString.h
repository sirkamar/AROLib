#ifndef ARO_ARM_STRINGREF_H
#define ARO_ARM_STRINGREF_H

#include <aro/core/arm/RefStream.h>

namespace aro {

/************************************************************************
*                         Ref<String> Declaration                       *
************************************************************************/

template <>
class Ref<String> : public RefBase
{
   public:
      Ref();
      virtual ~Ref();
      Ref(String* strPtr);
      Ref(const char* chStr);
      Ref(const wchar_t* chStr);
      Ref(Ref<String>&& strRef);
      Ref(const Ref<Null>& nRef);
      Ref(const Ref<String>& strRef);
      
      //type conversion
      explicit operator const wchar_t*() const;
      
      //dereference operator
      String* operator->() const;
      
      //assignment operator
      Ref<String>& operator=(String* str);
      Ref<String>& operator=(const char* chStr);
      Ref<String>& operator=(const wchar_t* chStr);
      Ref<String>& operator=(Ref<String>&& strRef);
      Ref<String>& operator=(const Ref<Null>& nRef);
      Ref<String>& operator=(const Ref<String>& strRef);
      
      //concatenation assginment operator
      Ref<String>& operator+=(const Ref<Object>& objRef);
      
      //concatenation operator
      Ref<String> operator+(const char* chStr) const;
      Ref<String> operator+(const wchar_t* chStr) const;
      Ref<String> operator+(const Ref<Object>& objRef) const;
      Ref<String> operator+(const Ref<String>& strRef) const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      String* ref;
   
   friend class Ref<Object>;
   friend class Weak<String>;
   template <class T> friend class Ref;
};

Ref<String> operator+(const char* chStr, const Ref<Object>& objRef);
Ref<String> operator+(const char* chStr, const Ref<String>& strRef);
Ref<String> operator+(const Ref<Object>& objRef, const char* chStr);
Ref<String> operator+(const wchar_t* chStr, const Ref<Object>& objRef);
Ref<String> operator+(const wchar_t* chStr, const Ref<String>& strRef);
Ref<String> operator+(const Ref<Object>& objRef, const wchar_t* chStr);
Ref<String> operator+(const Ref<Object>& objRef, const Ref<String>& strRef);

} /* namespace aro */

#endif /* ARO_ARM_STRINGREF_H */
