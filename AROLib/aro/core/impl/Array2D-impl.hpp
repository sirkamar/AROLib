#ifndef CORE_ARRAY2D_IMPL_H
#define CORE_ARRAY2D_IMPL_H

#include <aro/core/impl/Array-impl.hpp>
#include <aro/core/Array2D.hpp>

namespace aro {


template <class T>
Array<Array<T>>::Array()
   :Array<Array<T>>(0)
{
   
}

template <class T>
Array<Array<T>>::Array(vint rows)
   :Array<Array<T>>(rows, 0)
{
   
}

template <class T>
Array<Array<T>>::Array(vint rows, vint cols)
   :ArrayBase<RArray<T>>(rows)
{
   if(cols < 0)
      throw RException(new ArgumentException("Invalid Array2D dimensions: [" +
         String::valueOf(rows) + ", " + String::valueOf(cols) + "]"));
   
   for(vint n = 0; n<length; n++)
      item(n) = new Array<T>(cols);
}

template <class T>
Array<Array<T>>::Array(RArray2D<T> arr)
   :ArrayBase<RArray<T>>(arr->length)
{
   for(vint n = 0; n<length; n++)
      item(n) = new Array<T>(arr[n]);
}

template <class T>
Array<Array<T>>::Array(std::initializer_list<RArray<T>> elems)
   :ArrayBase<RArray<T>>(elems.size())
{
   vint n=0;
   for(RArray<T> arr : elems)
      item(n++) = new Array<T>(arr);
}

template <class T>
RArray2D<T> Array<Array<T>>::copyOf(vint count)
{
   return copyOf(0, count);
}

template <class T>
RArray2D<T> Array<Array<T>>::copyOf(vint offset, vint count)
{
   RArray2D<T> arr = new Array2D<T>(count);
   
   vint itemCount = Math::minimum(length, count);
   
   for(int n=0; n<itemCount; n++)
      arr[n] = item(n+offset)->copyOf(0, item(n+offset)->length);
   
   return arr;
}

template <class T>
void Array<Array<T>>::copy(vint dPos, RArray2D<T> src, vint sPos, vint num)
{
   ArrayBase<RArray<T>>::copyItems(dPos, src, sPos, num);
}

template <class T>
void Array<Array<T>>::readObject(io::RObjectInputStream is)
{
   ArrayBase<RArray<T>>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
       ArrayBase<RArray<T>>::item(n) = type_cast<Array<T>>(is->readObject());
}

template <class T>
void Array<Array<T>>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);
   
   for(vint n=0; n<length; n++)
      os->writeObject(item(n));
}

} /* namespace aro */

#endif /* CORE_ARRAY2D_IMPL_H */
