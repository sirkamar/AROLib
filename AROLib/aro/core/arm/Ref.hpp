/******************************************************************************
*               AUTOMATIC REFERENCE MANAGEMENT (ARM) NAMESPACE                *
*******************************************************************************
* Name        | class Ref<T>                                                  *
*             |                                                               *
* Author      | Kamar Morris                                                  *
*             |                                                               *
* Version     | 1.0                                                           *
*             |                                                               *
* Description | The template class Ref is like an upgraded C++ pointer. Refs  *
*             | (i.e. References) are designed to work in collaboration with  *
*             | the Garbage Collector to perform automatic memory monitoring  *
*             | and cleanup. The Garbage Collector monitors all of the Refs   *
*             | within an application and will automatically 'delete' memory  *
*             | allocated to an Object when there are no more Refs pointing   *
*             | to that Object.                                               *
*             |                                                               *
*             | A Ref must point to a class Object or Object-derived instance *
*             | dynamically allocated with the 'new' operator. Even when the  *
*             | Ref type is a class Interface derived type the Ref must point *
*             | to an instance of a class that inherits class Object.         *
*             |                                                               *
*             | Usage example:                                                *
*             | Ref<Object> obj = new Object();                               *
*             |                                                               *
*             | The template class Ref declares only operator members and is  *
*             | expected to be used in a similar manner as that of a pointer  *
*             | to a class instance by dereferencing it using the C++ arrow   *
*             | operator '->' to access the members of the class type being   *
*             | pointed to by the Ref.                                        *
*             |                                                               *
*             | See API documention for complete details.                     *
*             |                                                               *
*******************************************************************************
*                             REVISION HISTORY                                *
*******************************************************************************
* Date        Author         Version   Description                            *
* ----------  ---------      -------   -----------                            *
* YYYY/MM/DD  X. XXXXXX        X.X                                            *
*                                                                             *
* 2008/03/15  K. Morris        1.0     Created class.                         *
*                                                                             *
******************************************************************************/
#ifndef ARO_ARM_REF_H
#define ARO_ARM_REF_H

#include <aro/core/arm/RefNull.hpp>

namespace aro {

//template <class T>
//class Ref;
class Base;
template <class T>
class Weak;
class Object;
template <class U>
class RefItr;

namespace util {

template <class U>
interface Iterator;

}


template <template <class> class T, class U>
RefItr<U> getRefItr(const Ref<T<U>>& itr);


template <class U>
class RefItr
{
   public:
      RefItr& operator++();
      const Ref<U>& operator*() const;
      bool operator!=(const RefItr&) const;
   
   private:
      Ref<U> cur;
      const Ref<util::Iterator<U>> list;
      RefItr(const Ref<util::Iterator<U>>&);
   
   template <class T> friend class Ref;
   template <template <class> class T, U>
   friend RefItr<U> getRefItr(const Ref<T<U>>&);
};



class RefBase
{
   friend class Arm;
   template <class T>
   friend class Ref;
   friend struct ObjectInfo;
   template <class T>
   friend class RefArrayBase;
   
   RefBase() = default;
   
   protected:
      virtual void clear() = 0;
      virtual Base* ptr() const = 0;
   
   public:
      virtual ~RefBase() = default;
};

/***********************************************************************
*                           Ref<T> Declaration                         *
***********************************************************************/

template <class T>
class Ref : public RefBase
{
   public:
      Ref();
      Ref(T* tPtr);
      virtual ~Ref();
      Ref(Ref&& tRef) noexcept;
      template <class U>
      Ref(Ref<U>&& uRef) noexcept;
      Ref(const Ref& tRef);
      template <class U>
      Ref(const Ref<U>& uRef);
      Ref(const Ref<Null>& nRef);
      
      //dereference operator
      T* operator->() const;
      
      //assignment operator
      Ref& operator=(T* tPtr);
      Ref& operator=(Ref&& tRef) noexcept;
      template <class U>
      Ref& operator=(Ref<U>&& uRef);
      Ref& operator=(const Ref& tRef);
      template <class U>
      Ref& operator=(const Ref<U>& uRef);
      Ref& operator=(const Ref<Null>& nRef);
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      template <class U>
      RefItr<U> begin() const;
      
      template <class U>
      RefItr<U> end() const;
   
   protected:
      Base* ptr() const;
      void clear();
   
   private:
      T* ref;
   
   template <class U>
   friend class Ref;
   friend class Weak<T>;
};

} /* namespace aro */

#endif /* ARO_ARM_REF_H */
