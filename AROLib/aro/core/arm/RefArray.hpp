#ifndef ARO_ARM_ARRAYREF_H
#define ARO_ARM_ARRAYREF_H

#include <aro/core/arm/RefArrayBase.hpp>

namespace aro {

template <class T> class Array;

/************************************************************************
*                        Ref<Array<T>> Declaration                      *
************************************************************************/

template <class T>
class Ref<Array<T>> : public RefArrayBase<Ref<T>>
{
   public:
      Ref();
      virtual ~Ref();
      Ref(Array<T>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<T>>&& arrRef) noexcept;
      Ref(const Ref<Array<T>>& arrRef);
      template <class U>
      Ref(const Ref<Array<U>>& arrRef);
      Ref(std::initializer_list<Ref<T>> elems);

      //dereference operator
      Array<T>* operator->() const;

      //array subscript operator
      Ref<T>& operator[](int index);
      const Ref<T>& operator[](int index) const;

      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      template <class U>
      bool operator==(const Ref<Array<U>>& arrRef) const;
      template <class U>
      bool operator!=(const Ref<Array<U>>& arrRef) const;

      //assignment operator
      Ref<Array<T>>& operator=(Array<T>* arrPtr);
      Ref<Array<T>>& operator=(const Ref<Null>& nRef);
      Ref<Array<T>>& operator=(Ref<Array<T>>&& arrRef) noexcept;
      Ref<Array<T>>& operator=(const Ref<Array<T>>& arrRef);
      template <class U>
      Ref<Array<T>>& operator=(const Ref<Array<U>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<T>* ref;
      vbool crossAssigned;
   
   friend class Ref<Object>;
   friend class Weak<Array<T>>;
   template <class U> friend class Ref;
};


template <>
class Ref<Array<vint>> : public RefArrayBase<vint>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vint>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vint>>&& arrRef);
      Ref(const Ref<Array<vint>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vint> elems);
      
      //array subscript operator
      vint& operator[](int index);
      const vint& operator[](int index) const;
      
      //dereference operator
      Array<vint>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      //assignment operator
      Ref<Array<vint>>& operator=(Array<vint>* arrPtr);
      Ref<Array<vint>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vint>>& operator=(Ref<Array<vint>>&& arrRef);
      Ref<Array<vint>>& operator=(const Ref<Array<vint>>& arrRef);
      //template <class U>
      //Ref<Array<vint>>& operator=(const Ref<Array<U>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<vint>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vint>>;
   template <class T> friend class Ref;
};


template <>
class Ref<Array<vbool>> : public RefArrayBase<vbool>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vbool>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vbool>>&& arrRef);
      Ref(const Ref<Array<vbool>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vbool> elems);
      
      //array subscript operator
      vbool& operator[](int index);
      const vbool& operator[](int index) const;
      
      //dereference operator
      Array<vbool>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      //assignment operator
      Ref<Array<vbool>>& operator=(Array<vbool>* arrPtr);
      Ref<Array<vbool>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vbool>>& operator=(Ref<Array<vbool>>&& arrRef);
      Ref<Array<vbool>>& operator=(const Ref<Array<vbool>>& arrRef);
      //template <class T>
      //Ref<Array<vbool>>& operator=(const Ref<Array<T>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<vbool>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vbool>>;
   template <class T> friend class Ref;
};


template <>
class Ref<Array<vchar>> : public RefArrayBase<vchar>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vchar>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vchar>>&& arrRef);
      Ref(const Ref<Array<vchar>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vchar> elems);
      
      //array subscript operator
      vchar& operator[](int index);
      const vchar& operator[](int index) const;
      
      //dereference operator
      Array<vchar>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      //assignment operator
      Ref<Array<vchar>>& operator=(Array<vchar>* arrPtr);
      Ref<Array<vchar>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vchar>>& operator=(Ref<Array<vchar>>&& arrRef);
      Ref<Array<vchar>>& operator=(const Ref<Array<vchar>>& arrRef);
      //template <class T>
      //Ref<Array<vchar>>& operator=(const Ref<Array<T>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<vchar>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vchar>>;
   template <class T> friend class Ref;
};


template <>
class Ref<Array<vlong>> : public RefArrayBase<vlong>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vlong>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vlong>>&& arrRef);
      Ref(const Ref<Array<vlong>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vlong> elems);
      
      //array subscript operator
      vlong& operator[](int index);
      const vlong& operator[](int index) const;
      
      //dereference operator
      Array<vlong>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      //assignment operator
      Ref<Array<vlong>>& operator=(Array<vlong>* arrPtr);
      Ref<Array<vlong>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vlong>>& operator=(Ref<Array<vlong>>&& arrRef);
      Ref<Array<vlong>>& operator=(const Ref<Array<vlong>>& arrRef);
      //template <class T>
      //Ref<Array<vlong>>& operator=(const Ref<Array<T>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<vlong>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vlong>>;
   template <class T> friend class Ref;
};


template <>
class Ref<Array<vshort>> : public RefArrayBase<vshort>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vshort>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vshort>>&& arrRef);
      Ref(const Ref<Array<vshort>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vshort> elems);
      
      //array subscript operator
      vshort& operator[](int index);
      const vshort& operator[](int index) const;
      
      //dereference operator
      Array<vshort>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      //assignment operator
      Ref<Array<vshort>>& operator=(Array<vshort>* arrPtr);
      Ref<Array<vshort>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vshort>>& operator=(Ref<Array<vshort>>&& arrRef);
      Ref<Array<vshort>>& operator=(const Ref<Array<vshort>>& arrRef);
      //template <class T>
      //Ref<Array<vshort>>& operator=(const Ref<Array<T>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<vshort>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vshort>>;
   template <class T> friend class Ref;
};


template <>
class Ref<Array<vfloat>> : public RefArrayBase<vfloat>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vfloat>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vfloat>>&& arrRef);
      Ref(const Ref<Array<vfloat>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vfloat> elems);
      
      //array subscript operator
      vfloat& operator[](int index);
      const vfloat& operator[](int index) const;

      //dereference operator
      Array<vfloat>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;
      
      //assignment operator
      Ref<Array<vfloat>>& operator=(Array<vfloat>* arrPtr);
      Ref<Array<vfloat>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vfloat>>& operator=(Ref<Array<vfloat>>&& arrRef);
      Ref<Array<vfloat>>& operator=(const Ref<Array<vfloat>>& arrRef);
      //template <class T>
      //Ref<Array<vfloat>>& operator=(const Ref<Array<T>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();
   
   private:
      Array<vfloat>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vfloat>>;
   template <class T> friend class Ref;
};


template <>
class Ref<Array<vdouble>> : public RefArrayBase<vdouble>
{
   public:
      Ref();
      ~Ref();
      Ref(Array<vdouble>* arr);
      Ref(const Ref<Null>& nRef);
      Ref(Ref<Array<vdouble>>&& arrRef);
      Ref(const Ref<Array<vdouble>>& arrRef);
      //template <class T>
      //Ref(const Ref<Array<T>>& arrRef);
      Ref(std::initializer_list<vdouble> elems);
      
      //array subscript operator
      vdouble& operator[](int index);
      const vdouble& operator[](int index) const;

      //dereference operator
      Array<vdouble>* operator->() const;
      
      //equality/inequality operator
      bool operator==(const Ref<Object>& objRef) const;
      bool operator!=(const Ref<Object>& objRef) const;

      //assignment operator
      Ref<Array<vdouble>>& operator=(Array<vdouble>* arrPtr);
      Ref<Array<vdouble>>& operator=(const Ref<Null>& nRef);
      Ref<Array<vdouble>>& operator=(Ref<Array<vdouble>>&& arrRef);
      Ref<Array<vdouble>>& operator=(const Ref<Array<vdouble>>& arrRef);
      //template <class T>
      //Ref<Array<vdouble>>& operator=(const Ref<Array<T>>& arrRef);
   
   protected:
      Base* ptr() const;
      vint size() const;
      void clear();

   private:
      Array<vdouble>* ref;
   
   friend class Ref<Object>;
   friend class Weak<Array<vdouble>>;
   template <class T> friend class Ref;
};

/* Make uninstantiable */
template <class T>
class Ref<Array<Ref<T>>>
{
   Ref() = default;
};

} /* namespace aro */

#endif /* ARO_ARM_ARRAYREF_H */
