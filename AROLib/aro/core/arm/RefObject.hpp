#ifndef ARO_ARM_REFOBJECT_H
#define ARO_ARM_REFOBJECT_H

#include <aro/core/arm/RefTU.hpp>

namespace aro {

class String;
interface Interface;

/************************************************************************
*                        Ref<Object> Declaration                        *
************************************************************************/

template <>
class Ref<Object> : public RefBase
{
   public:
      Ref();
      virtual ~Ref();
      template <class T>
      Ref(Ref<T>&& tRef) noexcept;
      Ref(Object* objPtr);
      Ref(const char* chPtr);
      Ref(const wchar_t* chPtr);
      //Ref(Ref<String>&& strRef) noexcept;
      //Ref(const Ref<String>& strRef);
      template <class T>
      Ref(const Ref<T>& tRef);
      Ref(Ref<Object>&& objRef) noexcept;
      Ref(const Ref<Null>& nRef);
      Ref(const Ref<Object>& objRef);

      // dereference operator
      Object* operator->() const;
      
      // assignment operators
      template <class T>
      Ref<Object>& operator=(Ref<T>&& tRef) noexcept;
      Ref<Object>& operator=(Object* objPtr);
      Ref<Object>& operator=(const char* chPtr);
      Ref<Object>& operator=(const wchar_t* chPtr);
      //Ref<Object>& operator=(Ref<String>&& strRef) noexcept;
      //Ref<Object>& operator=(const Ref<String>& strRef);
      template <class T>
      Ref<Object>& operator=(const Ref<T>& tRef);
      Ref<Object>& operator=(Ref<Object>&& objRef) noexcept;
      Ref<Object>& operator=(const Ref<Null>& nRef);
      Ref<Object>& operator=(const Ref<Object>& objRef);

      // equality/inequality operators
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      Object* ref;
   
   friend class Weak<Object>;
   template <class T> friend class Ref;
   template <class T, class V> friend class RefArrayBase;
   template <class T> friend bool type_of(const Ref<Object>&);
   template <class T> friend Ref<T> type_cast(const Ref<Object>&);
};

// References to interface Interface are invalid
template <> class Ref<Interface>{Ref() = delete;};

} /* namespace aro */

#endif /* ARO_ARM_REFOBJECT_H */
