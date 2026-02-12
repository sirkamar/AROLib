#ifndef CORE_ARRAYBASE_IMPL_H
#define CORE_ARRAYBASE_IMPL_H

#include <aro/core/Math.hpp>
#include <aro/core/StringBuilder.hpp>
#include <aro/core/IndexException.hpp>
#include <aro/core/utils/CoreUtils.hpp>
#include <aro/io/ObjectInputStream.hpp>
#include <aro/io/ObjectOutputStream.hpp>
#include <aro/core/ArgumentException.hpp>

namespace aro {

template <class T>
ArrayBase<T>::ArrayBase()
   :length(0)
{
   // do not initialize
}

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
   
   array->init(); // allocate memory

   for(int n=0; n<array->length; n++)
      array->data[n] = data[n];
   
   return array;
}

template <class T>
RString ArrayBase<T>::toString()
{
    RStringBuilder buf = new StringBuilder(length * 13);

	buf->append("[");

    vbool afterFirst = false;
    for (vint i = 0; i < length; i++)
    {
        if (afterFirst)
            buf->append(", ");
        else
            afterFirst = true;

        buf->append(String::valueOf(data[i]));
    }

    return buf->append("]")->toString();
}

/* Protected Member Functions */

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
void ArrayBase<T>::resize(vint len)
{
   const_cast<vint&>(length) = len;
   
   init(); // reinitalize data array
}

template <class T>
void ArrayBase<T>::copyItems(vint dPos, Ref<ArrayBase<T>> src, vint sPos, vint num)
{
   src->checkIndex(sPos, true);

   checkIndex(dPos, true);

   checkIndex(num, true);
   
   if(num + dPos > length || num + sPos > src->length)
      throw RException(new ArgumentException("Too many elements to copy: " + String::valueOf(num)));
   
   for(vint i = 0; i<num; i++)
      data[dPos + i] = src->data[sPos + i];
}


/* Private Member Functions */

template <class T>
void ArrayBase<T>::init()
{
   data.reset(new T[length]);
}

template <class T>
void ArrayBase<T>::checkIndex(vint index, vbool includeLength) const
{
   if(index < 0 || index > (includeLength ? length : length-1))
      throw RException(new IndexException("Array index out of bounds: ", index));
}

} /* namespace aro */

#endif /* CORE_ARRAYBASE_IMPL_H */
