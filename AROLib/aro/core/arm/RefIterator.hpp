#ifndef ARO_ARM_REFITERABLE_H
#define ARO_ARM_REFITERABLE_H

#include <aro/core/arm/RefArray.hpp>

namespace aro {

namespace util {

template <class T>
interface Iterator;

}

/***********************************************************************
*                  Ref<util::Iterator<T>> Declaration                  *
***********************************************************************/

template <class T>
class Ref<util::Iterator<T>> : public RefBase
{
   public:
      Ref();
      ~Ref();
      template <class U>
      Ref(Ref<U>&& uRef);
      template <class U>
      Ref(const Ref<U>& uRef);
      Ref(const Ref<Null>& nRef);
      Ref(util::Iterator<T>* tPtr);
      Ref(Ref<util::Iterator<T>>&& tRef);
      Ref(const Ref<util::Iterator<T>>& tRef);
      
      //dereference operator
      util::Iterator<T>* operator->() const;

      //assignment operator
      Ref<util::Iterator<T>>& operator=(Ref&& tRef);
      template <class U>
      Ref<util::Iterator<T>>& operator=(Ref<U>&& uRef);
      Ref<util::Iterator<T>>& operator=(const Ref& tRef);
      template <class U>
      Ref<util::Iterator<T>>& operator=(const Ref<U>& uRef);
      Ref<util::Iterator<T>>& operator=(const Ref<Null>& nRef);
      Ref<util::Iterator<T>>& operator=(util::Iterator<T>* tPtr);

      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      class Itr
      {
         public:
            //dereference operator
            Itr& operator++();
            
            Ref<T>* operator->() const;
            
            const Ref<T>& operator*() const;
            
            bool operator!=(const Itr& itr) const;
         
         private:
            Ref<T> cur;
            
            Ref<util::Iterator<T>> list;
            
            Itr(const Ref<util::Iterator<T>>& lst, bool start);
         
         friend class Ref<util::Iterator<T>>;
      };
      
      //range-based-for
      Itr end() const;
      Itr begin() const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      util::Iterator<T>* ref;
   
   friend class Weak<T>;
   template <class U> friend class Ref;
   template <class T> friend class RefArrayBase;
};

} /* namespace aro */

#endif /* ARO_ARM_REFITERABLE_H */
