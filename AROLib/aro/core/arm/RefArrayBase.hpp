#ifndef ARO_ARM_ARRAYBASEREF_H
#define ARO_ARM_ARRAYBASEREF_H

#include <aro/core/arm/RefWeak.hpp>

namespace aro {

template <class T> class ArrayBase;

/************************************************************************
*                         RefArrayBase Declaration                      *
************************************************************************/

template <class T>
class RefArrayBase : public RefBase
{
   public:
      class Itr;
      
      virtual ~RefArrayBase();
      
      //enable range-based-for
      virtual Itr end() const final;
      virtual Itr begin() const final;
      
      //subscript operators
      virtual T& operator[](int) = 0;
      virtual const T& operator[](int) const = 0;
      
      //equality/inequality operators
      virtual bool operator==(const Ref<Object>& objRef) const = 0;
      virtual bool operator!=(const Ref<Object>& objRef) const = 0;
   
   protected:
      RefArrayBase();
      
      // nullify pointer
      virtual void clear() = 0;

      //get array pointer;
      virtual Base* ptr() const = 0;

      //get array size
      virtual vint size() const = 0;
   
   friend class Itr;
   friend class Ref<T>;
   friend class Ref<Object>;
};

template <class T>
class RefArrayBase<T>::Itr
{
   public:
      Itr& operator++();
      const T& operator*() const;
      bool operator!=(const Itr&) const;
   
   private:
      int pos;

      const RefArrayBase<T>& arr;
      
      Itr(const RefArrayBase<T>&, vint);
   
   friend class RefArrayBase<T>;
};

} /* namespace aro */

#endif /* ARO_ARM_ARRAYBASEREF_H */
