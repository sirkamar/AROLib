#ifndef ARM_REFTU_H
#define ARM_REFTU_H

#include <aro/core/arm/Ref.hpp>

namespace aro {

template <template <typename> class T, class U>
class Ref<T<U>> : public RefBase
{
   public:
      Ref();
      Ref(T<U>* tPtr);
      virtual ~Ref();
      Ref(Ref&& tRef);
      template <class V>
      Ref(const Ref<V>& vRef);
      //template <template <typename> class V>
      //Ref(Ref<V<U>>&& uRef);
      Ref(const Ref& tRef);
      //template <template <typename> class V>
      //Ref(const Ref<V<U>>& uRef);
      Ref(const Ref<Null>& nRef);
      
      //dereference operator
      T<U>* operator->() const;
      
      //assignment operator
      Ref& operator=(T<U>* tPtr);
      Ref& operator=(Ref&& tRef);
      template <class V>
      Ref& operator=(const Ref<V>& vRef);
      //template <class V>
      //Ref& operator=(Ref<T<V>>&& uRef);
      Ref& operator=(const Ref& tRef);
      //template <class V>
      //Ref& operator=(const Ref<T<V>>& uRef);
      Ref& operator=(const Ref<Null>& nRef);
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      class Itr
      {
         public:
            Itr& operator++();
            const Ref<U>& operator*() const;
            bool operator!=(const Itr&) const;
         
         private:
            Ref<U> cur;
            const Ref<util::Iterator<U>> list;
            Itr(const Ref<util::Iterator<U>>&);
         
         friend class Ref<T<U>>;
      };
      
      Itr begin() const;
      Itr end() const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      T<U>* ref;
   
   friend class Weak<T<U>>;
   template <class V> friend class Ref;
};

} /* namespace aro */

#endif // !ARM_REFTU_H
