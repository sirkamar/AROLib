#ifndef ARO_ARM_ARRAYBASEREF_H
#define ARO_ARM_ARRAYBASEREF_H

#include <aro/core/arm/RefWeak.hpp>

namespace aro {

template <class T> class Array;
template <class T> class ArrayBase;

/************************************************************************
*                         RefArrayBase Declaration                      *
************************************************************************/

template <class T, class V>
class RefArrayBase : public RefBase
{
   public:
      class Itr;
      
      virtual ~RefArrayBase();
      
      //enable range-based-for
      virtual Itr end() const final;
      virtual Itr begin() const final;

      //dereference operator
      Array<T>* operator->() const;
      
      //subscript operators
      virtual V& operator[](int) = 0;
      virtual const V& operator[](int) const = 0;
      
      //equality/inequality operators
      virtual bool operator==(const Ref<Object>& objRef) const = 0;
      virtual bool operator!=(const Ref<Object>& objRef) const = 0;
   
   protected:
      Array<T>* ref;

      RefArrayBase();
      
      // nullify pointer
      virtual void clear() = 0;

      //get array pointer;
      virtual Base* ptr() const = 0;

      //get array size
      virtual vint size() const = 0;
   
   friend typename Itr;
   friend class Ref<T>;
   friend class Ref<Object>;
};

template <class T, class V>
class RefArrayBase<T,V>::Itr
{
   public:
      Itr& operator++();
      const V& operator*() const;
      bool operator!=(const Itr&) const;
   
   private:
      int pos;

      const RefArrayBase<T,V>& arr;
      
      Itr(const RefArrayBase<T,V>&, vint);
   
   friend class RefArrayBase<T,V>;
};

} /* namespace aro */

#endif /* ARO_ARM_ARRAYBASEREF_H */
