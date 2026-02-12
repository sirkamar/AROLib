#ifndef CORE_ARRAY2D_H
#define CORE_ARRAY2D_H

#include <aro/core/Array.hpp>

namespace aro {

template <class T>
using Array2D = Array<Array<T>>;

template <class T>
using RArray2D = Ref<Array2D<T>>;

template <class T>
class Array<Array<T>> final extends public ArrayBase<RArray<T>> implements public Cloneable<Array2D<T>>, public io::Streamable<Array2D<T>>
{
   public:
      Array(vint rows);
      Array(RArray2D<T> arr);
      Array(vint rows, vint cols);
      
      virtual RArray2D<T> copyOf(vint size);
      virtual RArray2D<T> copyOf(vint offset, vint size);
      virtual void copy(vint offset, RArray2D<T> src, vint srcOffset, vint num);
   
   protected:
       virtual void readObject(io::RObjectInputStream is);
       virtual void writeObject(io::RObjectOutputStream os);
   
   private:
       Array(); // Reserved for ObjectInputStream
       Array(std::initializer_list<RArray<T>> elems);
   
   friend class Ref<Array2D<T>>;
   friend class RefArrayBase<Array<T>,RArray<T>>;
   friend interface Cloneable<Array2D<T>>;
   friend interface io::Streamable<Array2D<T>>;
};

//template <class T>
//class Array2D : public Array<Array<T>>, public io::Streamable<Array2D<T>>
//{
//   public:
//      Array2D(vint rows);
//      Array2D(RArray2D<T> arr);
//      Array2D(vint rows, vint cols);
//   
//   protected:
//      Array2D(); // Reserved for ObjectInputStream
//      Array2D(std::initializer_list<RArray<T>> elems);
//      
//      virtual void readObject(io::RObjectInputStream is);
//      virtual void writeObject(io::RObjectOutputStream os);
//   
//   friend interface io::Streamable<Array2D<T>>;
//};

} /* namespace aro */

#endif /* CORE_ARRAY2D_H */
