#ifndef ARO_ARM_STREAMREF_H
#define ARO_ARM_STREAMREF_H

#include <aro/core/arm/RefComp.hpp>

namespace aro {

namespace io {

template <class T>
interface Streamable;

}

/************************************************************************
*                 Ref<io::Streamable<String>> Declaration               *
************************************************************************/

template <>
class Ref<io::Streamable<String>> : public RefBase
{
   public:
      Ref();
      virtual ~Ref();
      Ref(const char* chStr);
      Ref(const wchar_t* chStr);
      Ref(Ref<String>&& strRef) noexcept;
      Ref(const Ref<Null>& nRef);
      Ref(const Ref<String>& strRef);
      Ref(io::Streamable<String>* strPtr);
      Ref(Ref<io::Streamable<String>>&& strRef) noexcept;
      Ref(const Ref<io::Streamable<String>>& strRef);

      //dereference operator
      io::Streamable<String>* operator->() const;
      
      //assignment operator
      Ref<io::Streamable<String>>& operator=(const char* chStr);
      Ref<io::Streamable<String>>& operator=(const wchar_t* chStr);
      Ref<io::Streamable<String>>& operator=(Ref<String>&& strRef) noexcept;
      Ref<io::Streamable<String>>& operator=(const Ref<Null>& nRef);
      Ref<io::Streamable<String>>& operator=(const Ref<String>& strRef);
      Ref<io::Streamable<String>>& operator=(io::Streamable<String>* strPtr);
      Ref<io::Streamable<String>>& operator=(Ref<io::Streamable<String>>&& strRef) noexcept;
      Ref<io::Streamable<String>>& operator=(const Ref<io::Streamable<String>>& strRef);

      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      io::Streamable<String>* ref;
   
   friend class Ref<Object>;
   template <class T> friend class Ref;
   friend class Weak<io::Streamable<String>>;
};

} /* namespace aro */

#endif /* ARO_ARM_STREAMREF_H */
