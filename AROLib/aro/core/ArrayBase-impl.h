#ifndef CORE_ARRAYBASE_IMPL_H
#define CORE_ARRAYBASE_IMPL_H

#include <aro/core/Math.h>
#include <aro/core/utils/Utils.h>
#include <aro/core/ArgumentException.h>
#include <aro/core/IndexException.h>
#include <aro/io/ObjectInputStream.h>
#include <aro/io/ObjectOutputStream.h>

namespace aro {

template <class T>
ArrayBase<T>::ArrayBase(vint size)
   :length(size)
{
   if(size < 0)
      throw RException(new ArgumentException("Negative Array length: " +
                                         String::valueOf(size)));
   
   init();
}

template <class T>
ArrayBase<T>::ArrayBase(Ref<ArrayBase<T>> arr)
   :length(arr->length)
{
   init();
   
   for(vint i = 0; i<length; i++)
      data[i] = arr->data[i];
}

//template <class T> template <class U>
//ArrayBase<T>::ArrayBase(Ref<ArrayBase<U>> arr)
//   :length(arr->length)
//{
//   init();
//   
//   for(vint i=0; i<length; i++)
//      data[i] = arr->data[i];
//}

template <class T>
ArrayBase<T>::ArrayBase(std::initializer_list<T> elems)
:length(elems.size())
{
   init();

   int n = 0;

   for(T e : elems)
      data[n++] = e;
}

template <class T>
vint ArrayBase<T>::getLenth()
{
   return length;
}

template <class T>
T ArrayBase<T>::get(vint index)
{
   return item(index);
}

template <class T>
void ArrayBase<T>::set(vint index, T value)
{
   item(index) = value;
}

template <class T>
RObject ArrayBase<T>::clone()
{
   Ref<ArrayBase<T>> array = type_cast<ArrayBase<T>>(Object::clone());
   
   for(int n=0; n<array->length; n++)
      array->data[n] = data[n];
   
   return array;
}


/* Protected Member Functions */

template <class T>
void ArrayBase<T>::finalize()
{
   freeMemory();
   
   Object::finalize();
}

template <class T>
T& ArrayBase<T>::item(vint index)
{
   checkIndex(index);
   
   return data[index];
}

template <class T>
const T& ArrayBase<T>::item(vint index) const
{
   checkIndex(index);
   
   return data[index];
}

template <class T>
void ArrayBase<T>::setLength(vint len)
{
   const_cast<vint&>(length) = len;
   
   freeMemory();
   
   init();
}

template <class T>
void ArrayBase<T>::copyItems(vint dPos, Ref<ArrayBase<T>> src, vint sPos, vint num)
{
   //checkIndex(dPos);
   if(dPos < 0 || dPos > length)
      throw RException(new IndexException("Array index out of bounds: ", dPos));
   
   //src->checkIndex(sPos);
   if(sPos < 0 || sPos > src->length)
      throw RException(new IndexException("Array index out of bounds: ", sPos));
   
   if(num > length - dPos || num > src->length - sPos)
      throw RException(new ArgumentException("Too many elements to copy: " + String::valueOf(num)));
   
   for(vint i = 0; i<num; i++)
      data[dPos + i] = src->data[sPos + i];
}


/* Private Member Functions */

template <class T>
void ArrayBase<T>::init()
{
   data = new T[length];
}

template <class T>
void ArrayBase<T>::freeMemory()
{
   delete [] data;
}

template <class T>
void ArrayBase<T>::checkIndex(vint index) const
{
   if(index < 0 || index >= length)
      throw RException(new IndexException("Array index out of bounds: ", index));
}

} /* namespace aro */

#endif /* CORE_ARRAYBASE_IMPL_H */
