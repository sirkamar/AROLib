#ifndef CORE_ARRAYIMP_H
#define CORE_ARRAYIMP_H

//#include <aro/core/Array.h>
#include <aro/core/ArrayBase_.h>

namespace aro {

template <class T>
Array<T>::Array()
   :Array<T>(0)
{
   
}

template <class T>
Array<T>::Array(vint size)
   :ArrayBase<Ref<T>>(size)
{
   
}

template <class T>
Array<T>::Array(RArray<T> arr)
   :ArrayBase<Ref<T>>(arr)
{
   
}

template <class T>
Array<T>::Array(std::initializer_list<Ref<T>> elems)
   :ArrayBase<Ref<T>>(elems)
{
   
}

template <class T>
RArray<T> Array<T>::copyOf(vint count)
{
   return copyOf(0, count);
}

template <class T>
RArray<T> Array<T>::copyOf(vint offset, vint count)
{
   RArray<T> arr = new Array<T>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

template <class T>
void Array<T>::copy(vint dPos, RArray<T> src, vint sPos, vint num)
{
   ArrayBase<Ref<T>>::copyItems(dPos, src, sPos, num);
}

template <class T>
void Array<T>::readObject(io::RObjectInputStream is)
{
   setLength(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = type_cast<T>(is->readObject());
}

template <class T>
void Array<T>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);
   
   for(vint n=0; n<length; n++)
      os->writeObject(item(n));
}


} /* namespace aro */

#endif /* CORE_ARRAYIMP_H */
