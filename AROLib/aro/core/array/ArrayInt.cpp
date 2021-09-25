#ifndef CORE_ARRAYIMP_H
#define CORE_ARRAYIMP_H

#include <aro/core/Math.h>
#include <aro/core/utils/Utils.h>
#include <aro/core/ArgException.h>
#include <aro/core/IndexException.h>
#include <aro/io/ObjectInputStream.h>
#include <aro/io/ObjectOutputStream.h>

namespace aro {

   template <class T>
   Array<T>::Array(vint size)
      :length(size)
   {
      if(size < 0)
         throw RException(new ArgException("Negative Array length: " +
         String::valueOf(size)));

      init();
   }

   template <class T>
   Array<T>::Array(RArray<T> arr)
      :length(arr->length)
   {
      init();

      copy(0, arr, 0, length);
   }

   template <class T> template <class U>
   Array<T>::Array(RArray<U> arr)
      :length(arr->length)
   {
      init();

      for(vint i = 0; i<length; i++)
         data[i] = arr->data[i];
   }

   template <class T>
   vint Array<T>::getLenth()
   {
      return length;
   }

   template <class T>
   RArray<T> Array<T>::copyOf(vint count)
   {
      return copyOf(0, count);
   }

   template <class T>
   RArray<T> Array<T>::copyOf(vint offset, vint count)
   {
      RArray<T> arr(new Array<T>(count));

      arr->copy(0, this, offset, Math::minimum(length, count));

      return arr;
   }

   template <class T>
   void Array<T>::copy(vint dPos, RArray<T> src, vint sPos, vint num)
   {
      if(dPos < 0 || dPos >= length)
         throw RException(new IndexException("Dst Array index out of bounds: ", dPos));

      if(sPos < 0 || sPos >= src->length)
         throw RException(new IndexException("Src Array index out of bounds: ", sPos));

      if(num > length - dPos || num > src->length - sPos)
         throw RException(new ArgException("Too many elements to copy: " + String::valueOf(num)));

      for(vint i = 0; i<num; i++)
         data[dPos + i] = src->data[sPos + i];
   }

   template <class T>
   const T& Array<T>::get(int index)
   {
      if(index < 0 || index >= length)
         throw RException(new IndexException("Array index out of bounds: ", index));

      return data[index];
   }

   template <class T>
   void Array<T>::set(int index, const T& item)
   {
      if(index < 0 || index >= length)
         throw RException(new IndexException("Array index out of bounds: ", index));

      data[index] = item;
   }

   template <class T>
   Ref<T> getObject(io::RObjectInputStream is, Ref<T>*)
   {
      return type_cast<T>(is->readObject());
   }

   template <class T>
   void Array<T>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = getObject(is, (T*)nullptr);
   }

   template<>
   inline void Array<vint>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readInt();
   }

   template<>
   inline void Array<vbool>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readBool();
   }

   template<>
   inline void Array<vchar>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readChar();
   }

   template<>
   inline void Array<vlong>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readLong();
   }

   template<>
   inline void Array<vfloat>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readFloat();
   }

   template<>
   inline void Array<vshort>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readShort();
   }

   template<>
   inline void Array<vdouble>::readObject(io::RObjectInputStream is)
   {
      readLength(is);

      for(vint n = 0; n<length; n++)
         data[n] = is->readDouble();
   }

   template <class T>
   void Array<T>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeObject(data[n]);
   }

   template <>
   inline void Array<vint>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeInt(data[n]);
   }

   template <>
   inline void Array<vbool>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeBool(data[n]);
   }

   template <>
   inline void Array<vchar>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeChar(data[n]);
   }

   template <>
   inline void Array<vlong>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeLong(data[n]);
   }

   template <>
   inline void Array<vfloat>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeFloat(data[n]);
   }

   template <>
   inline void Array<vshort>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeShort(data[n]);
   }

   template <>
   inline void Array<vdouble>::writeObject(io::RObjectOutputStream os)
   {
      os->writeInt(length);

      for(vint n = 0; n<length; n++)
         os->writeDouble(data[n]);
   }

   /* Protected Member Functions */

   template <class T>
   void Array<T>::finalize()
   {
      freeMemory();

      Object::finalize();
   }

   /* Private Member Functions */

   // Reserved for use by
   // ObjectInputStream
   template <class T>
   Array<T>::Array()
      :length(0)
   {
      init();
   }

   template <class T>
   Array<T>::Array(std::initializer_list<T> elems)
      :length(elems.size())
   {
      init();

      int n = 0;

      for(T e : elems)
         data[n++] = e;
   }

   template <class T>
   void Array<T>::init()
   {
      data = new T[length];
   }

   template <class T>
   void Array<T>::freeMemory()
   {
      delete[] data;
   }

   template <class T>
   T& Array<T>::item(vint index)
   {
      if(index < 0 || index >= length)
         throw RException(new IndexException("Array Index out of bounds: ", index));

      return data[index];
   }

   template <class T>
   const T& Array<T>::item(vint index) const
   {
      if(index < 0 || index >= length)
         throw RException(new IndexException("Array Index out of bounds: ", index));

      return data[index];
   }

   template <class T>
   void Array<T>::readLength(io::RObjectInputStream is)
   {
      const_cast<vint&>(length) = is->readInt();

      freeMemory();

      init();
   }

} /* namespace aro */

#endif /* CORE_ARRAYIMP_H */
