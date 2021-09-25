#ifndef CORE_ARRAY2DIMP_H
#define CORE_ARRAY2DIMP_H

#include <aro/core/Array_.h>
#include <aro/core/Array2D.h>

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
   if(cols < 0){
      ArrayBase<RArray<T>>::finalize(); // undo memory allocation
      
      throw RException(new ArgumentException("Invalid Array2D dimensions: [" +
         String::valueOf(rows) + ", " + String::valueOf(cols) + "]"));
   }
   
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
   
   //arr->copy(0, thisref, offset, itemCount);
   
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
   setLength(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = type_cast<Array<T>>(is->readObject());
}

template <class T>
void Array<Array<T>>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);
   
   for(vint n=0; n<length; n++)
      os->writeObject(item(n));
}



//template <class T>
//Array2D<T>::Array2D()
//   :Array2D<T>(0)
//{
//   
//}
//
//template <class T>
//Array2D<T>::Array2D(vint rows)
//   :Array2D<T>(rows, 0)
//{
//   
//}
//
//template <class T>
//Array2D<T>::Array2D(vint rows, vint cols)
//   :Array<Array<T>>(rows)
//{
//   if(cols < 0)
//      throw RException(new ArgumentException("Invalid Array2D dimensions: [" +
//            String::valueOf(rows) + ", " + String::valueOf(cols) + "]"));
//   
//   for(vint n=0; n<length; n++)
//      item(n) = new Array<T>(cols);
//}
//
//template <class T>
//Array2D<T>::Array2D(RArray2D<T> arr)
//   :Array<Array<T>>(arr->length)
//{
//   for(vint n=0; n<length; n++)
//      item(n) = new Array<T>(arr[n]);
//}
//
//template <class T>
//Array2D<T>::Array2D(std::initializer_list<RArray<T>> elems)
//   :Array<Array<T>>(elems.size())
//{
//   for(RArray<T> arr : elems)
//      item(n) = new Array<T>(arr);
//}
//
//template <class T>
//void Array2D<T>::readObject(io::RObjectInputStream is)
//{
//   Array<Array<T>>::readObject(is);
//}
//
//template <class T>
//void Array2D<T>::writeObject(io::RObjectOutputStream os)
//{
//   Array<Array<T>>::writeObject(os);
//}

} /* namespace aro */

#endif /* CORE_ARRAY2DIMP_H */
