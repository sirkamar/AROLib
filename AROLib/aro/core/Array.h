#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H

#include <aro/io/Streamable.h>
#include <aro/core/ArrayBase.h>

namespace aro {

template <class T>
using RArray = Ref<Array<T>>;

/** The template class Array is an encapsulation of
* the standard Array type into an object type with
* error checking ability. Can be used for any of
* the built-in value types or reference types.
* E.g. RArray<vint> arr = new Array<vint>(5); */
template <class T>
class Array final : public ArrayBase<Ref<T>>, public Cloneable<Array<T>>, public io::Streamable<Array<T>>
{
   public:
      Array(vint size);
      Array(RArray<T> arr);
      
      virtual RArray<T> copyOf(vint size);
      virtual RArray<T> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<T> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<Ref<T>> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<T>>;
   friend class RefArrayBase<T>;
   friend interface Cloneable<Array<T>>;
   friend interface io::Streamable<Array<T>>;
};


template<>
class Array<vint> final : public ArrayBase<vint>, public Cloneable<Array<vint>>, public io::Streamable<Array<vint>>
{
   public:
      Array(vint size);
      Array(RArray<vint> arr);
      
      virtual RArray<vint> copyOf(vint size);
      virtual RArray<vint> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vint> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vint> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vint>>;
   friend class RefArrayBase<vint>;
   friend interface Cloneable<Array<vint>>;
   friend interface io::Streamable<Array<vint>>;
};


template<>
class Array<vchar> final : public ArrayBase<vchar>, public Cloneable<Array<vchar>>, public io::Streamable<Array<vchar>>
{
   public:
      Array(vint size);
      Array(RArray<vchar> arr);
      
      virtual RArray<vchar> copyOf(vint size);
      virtual RArray<vchar> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vchar> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vchar> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vchar>>;
   friend class RefArrayBase<vchar>;
   friend interface Cloneable<Array<vchar>>;
   friend interface io::Streamable<Array<vchar>>;
};


template<>
class Array<vbool> final : public ArrayBase<vbool>, public Cloneable<Array<vbool>>, public io::Streamable<Array<vbool>>
{
   public:
      Array(vint size);
      Array(RArray<vbool> arr);
      
      virtual RArray<vbool> copyOf(vint size);
      virtual RArray<vbool> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vbool> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vbool> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vbool>>;
   friend class RefArrayBase<vbool>;
   friend interface Cloneable<Array<vbool>>;
   friend interface io::Streamable<Array<vbool>>;
};


template<>
class Array<vlong> final : public ArrayBase<vlong>, public Cloneable<Array<vlong>>, public io::Streamable<Array<vlong>>
{
   public:
      Array(vint size);
      Array(RArray<vlong> arr);
      
      virtual RArray<vlong> copyOf(vint size);
      virtual RArray<vlong> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vlong> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vlong> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vlong>>;
   friend class RefArrayBase<vlong>;
   friend interface Cloneable<Array<vlong>>;
   friend interface io::Streamable<Array<vlong>>;
};


template<>
class Array<vfloat> final : public ArrayBase<vfloat>, public Cloneable<Array<vfloat>>, public io::Streamable<Array<vfloat>>
{
   public:
      Array(vint size);
      Array(RArray<vfloat> arr);
      
      virtual RArray<vfloat> copyOf(vint size);
      virtual RArray<vfloat> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vfloat> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vfloat> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vfloat>>;
   friend class RefArrayBase<vfloat>;
   friend interface Cloneable<Array<vfloat>>;
   friend interface io::Streamable<Array<vfloat>>;
};


template<>
class Array<vshort> final : public ArrayBase<vshort>, public Cloneable<Array<vshort>>, public io::Streamable<Array<vshort>>
{
   public:
      Array(vint size);
      Array(RArray<vshort> arr);
      
      virtual RArray<vshort> copyOf(vint size);
      virtual RArray<vshort> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vshort> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vshort> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vshort>>;
   friend class RefArrayBase<vshort>;
   friend interface Cloneable<Array<vshort>>;
   friend interface io::Streamable<Array<vshort>>;
};


template<>
class Array<vdouble> final : public ArrayBase<vdouble>, public Cloneable<Array<vdouble>>, public io::Streamable<Array<vdouble>>
{
   public:
      Array(vint size);
      Array(RArray<vdouble> arr);
      
      virtual RArray<vdouble> copyOf(vint size);
      virtual RArray<vdouble> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray<vdouble> src, vint srcOffset, vint num);
   
   protected:
      Array(); // reserved for ObjectInputStream
      Array(std::initializer_list<vdouble> elems); // Array sequence constructor
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   friend class Ref<Array<vdouble>>;
   friend class RefArrayBase<vdouble>;
   friend interface Cloneable<Array<vdouble>>;
   friend interface io::Streamable<Array<vdouble>>;
};


} /* namespace aro */

#endif /* CORE_ARRAY_H */
