#ifndef ARO_ARM_COMPREF_H
#define ARO_ARM_COMPREF_H

#include <aro/core/arm/RefIterator.hpp>

namespace aro {

//class String;

template <class T>
interface Comparable;

/************************************************************************
*                  Ref<Comparable<String>> Declaration                  *
************************************************************************/

template <>
class Ref<Comparable<String>> : public RefBase
{
   public:
      Ref();
      virtual ~Ref();
      Ref(const char* chStr);
      Ref(Ref<String>&& strRef);
      Ref(const Ref<Null>& nRef);
      Ref(const Ref<String>& strRef);
      Ref(Comparable<String>* strPtr);
      Ref(Ref<Comparable<String>>&& strRef);
      Ref(const Ref<Comparable<String>>& strRef);
      
      //dereference operator
      Comparable<String>* operator->() const;
      
      //assignment operator
      Ref<Comparable<String>>& operator=(const char* chStr);
      Ref<Comparable<String>>& operator=(Ref<String>&& strRef);
      Ref<Comparable<String>>& operator=(const Ref<Null>& nRef);
      Ref<Comparable<String>>& operator=(const Ref<String>& strRef);
      Ref<Comparable<String>>& operator=(Comparable<String>* strPtr);
      Ref<Comparable<String>>& operator=(Ref<Comparable<String>>&& strRef);
      Ref<Comparable<String>>& operator=(const Ref<Comparable<String>>& strRef);
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      Comparable<String>* ref;
   
   friend class Ref<Object>;
   template <class T> friend class Ref;
   friend class Weak<Comparable<String>>;
};

} /* namespace aro */

#endif /* ARO_ARM_COMPREF_H */
