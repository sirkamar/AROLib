#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H

#include <aro/io/Streamable.hpp>
#include <aro/core/ArrayBase.hpp>

namespace aro {

template <class T>
using RArray = Ref<Array<T>>;

/** The template class Array is an encapsulation of
 the standard array type into an object type with
 error checking ability. Can be used for any of
 the built-in value types or reference types.
 E.g. RArray<vint> arr = new Array<vint>(5); */
template <class T>
class Array final extends public ArrayBase<Ref<T>> implements public Cloneable<Array<T>>, public io::Streamable<Array<T>>
{
   public:
      Array(vint size);
      Array(RArray<T> arr);
      
      virtual RArray<T> copyOf(vint size);
      virtual RArray<T> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<T> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
       Array(); // required by Streamable
       Array(std::initializer_list<Ref<T>> elems); // Array sequence constructor
   
   friend class Ref<Array<T>>;
   friend class RefArrayBase<T,Ref<T>>;
   friend interface Cloneable<Array<T>>;
   friend interface io::Streamable<Array<T>>;
};


template<>
class Array<vint> final extends public ArrayBase<vint> implements public Cloneable<Array<vint>>, public io::Streamable<Array<vint>>
{
   public:
      Array(vint size);
      Array(RArray<vint> arr);
      
      virtual RArray<vint> copyOf(vint size);
      virtual RArray<vint> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vint> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vint> elems); // Array sequence constructor
   
   friend class Ref<Array<vint>>;
   friend class RefArrayBase<vint,vint>;
   friend interface Cloneable<Array<vint>>;
   friend interface io::Streamable<Array<vint>>;
};


template<>
class Array<vchar> final extends public ArrayBase<vchar> implements public Cloneable<Array<vchar>>, public io::Streamable<Array<vchar>>
{
   public:
      Array(vint size);
      Array(RArray<vchar> arr);
      
      virtual RArray<vchar> copyOf(vint size);
      virtual RArray<vchar> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vchar> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vchar> elems); // Array sequence constructor
   
   friend class Ref<Array<vchar>>;
   friend class RefArrayBase<vchar,vchar>;
   friend interface Cloneable<Array<vchar>>;
   friend interface io::Streamable<Array<vchar>>;
};


template<>
class Array<vbool> final extends public ArrayBase<vbool> implements public Cloneable<Array<vbool>>, public io::Streamable<Array<vbool>>
{
   public:
      Array(vint size);
      Array(RArray<vbool> arr);
      
      virtual RArray<vbool> copyOf(vint size);
      virtual RArray<vbool> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vbool> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vbool> elems); // Array sequence constructor
   
   friend class Ref<Array<vbool>>;
   friend class RefArrayBase<vbool,vbool>;
   friend interface Cloneable<Array<vbool>>;
   friend interface io::Streamable<Array<vbool>>;
};


template<>
class Array<vlong> final extends public ArrayBase<vlong> implements public Cloneable<Array<vlong>>, public io::Streamable<Array<vlong>>
{
   public:
      Array(vint size);
      Array(RArray<vlong> arr);
      
      virtual RArray<vlong> copyOf(vint size);
      virtual RArray<vlong> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vlong> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vlong> elems); // Array sequence constructor
   
   friend class Ref<Array<vlong>>;
   friend class RefArrayBase<vlong,vlong>;
   friend interface Cloneable<Array<vlong>>;
   friend interface io::Streamable<Array<vlong>>;
};


template<>
class Array<vfloat> final extends public ArrayBase<vfloat> implements public Cloneable<Array<vfloat>>, public io::Streamable<Array<vfloat>>
{
   public:
      Array(vint size);
      Array(RArray<vfloat> arr);
      
      virtual RArray<vfloat> copyOf(vint size);
      virtual RArray<vfloat> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vfloat> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vfloat> elems); // Array sequence constructor
   
   friend class Ref<Array<vfloat>>;
   friend class RefArrayBase<vfloat,vfloat>;
   friend interface Cloneable<Array<vfloat>>;
   friend interface io::Streamable<Array<vfloat>>;
};


template<>
class Array<vshort> final extends public ArrayBase<vshort> implements public Cloneable<Array<vshort>>, public io::Streamable<Array<vshort>>
{
   public:
      Array(vint size);
      Array(RArray<vshort> arr);
      
      virtual RArray<vshort> copyOf(vint size);
      virtual RArray<vshort> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vshort> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vshort> elems); // Array sequence constructor
   
   friend class Ref<Array<vshort>>;
   friend class RefArrayBase<vshort,vshort>;
   friend interface Cloneable<Array<vshort>>;
   friend interface io::Streamable<Array<vshort>>;
};


template<>
class Array<vdouble> final extends public ArrayBase<vdouble> implements public Cloneable<Array<vdouble>>, public io::Streamable<Array<vdouble>>
{
   public:
      Array(vint size);
      Array(RArray<vdouble> arr);
      
      virtual RArray<vdouble> copyOf(vint size);
      virtual RArray<vdouble> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vdouble> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vdouble> elems); // Array sequence constructor
   
   friend class Ref<Array<vdouble>>;
   friend class RefArrayBase<vdouble,vdouble>;
   friend interface Cloneable<Array<vdouble>>;
   friend interface io::Streamable<Array<vdouble>>;
};


} /* namespace aro */

#endif /* CORE_ARRAY_H */
