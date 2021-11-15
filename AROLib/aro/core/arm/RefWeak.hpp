#ifndef ARO_ARM_WEAKREF_H
#define ARO_ARM_WEAKREF_H

#include <aro/core/arm/RefObject.hpp>

namespace aro {

template <class T>
class Ref<Weak<T>> : public RefBase
{
   public:
      Ref();
      virtual ~Ref();
      Ref(Weak<T>* wPtr);
      Ref(const Ref<T>& tRef);
      Ref(Ref<Weak<T>>&& wRef);
      Ref(const Ref<Null>& nRef);
      Ref(const Ref<Weak<T>>& wRef);

      Weak<T>* operator->() const;
      
      Ref<Weak<T>>& operator=(Weak<T>* tPtr);
      Ref<Weak<T>>& operator=(const Ref<T>& tRef);
      Ref<Weak<T>>& operator=(Ref<Weak<T>>&& wRef);
      Ref<Weak<T>>& operator=(const Ref<Null>& nRef);
      Ref<Weak<T>>& operator=(const Ref<Weak<T>>& wRef);
      
      bool operator==(const Ref<Object>& tRef) const;
      bool operator!=(const Ref<Object>& tRef) const;
   
   protected:
      Base* ptr() const;
      void clear();

   private:
      Weak<T>* ref;
   
   friend class Ref<Object>;
};

template <class T>
class Ref<Weak<Ref<T>>>
{
   Ref() = default;
};

} /* namespace aro */

#endif /* ARO_ARM_WEAKREF_H */
