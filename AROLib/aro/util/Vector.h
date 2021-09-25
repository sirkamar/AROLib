#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include <aro/util/AbstractList.h>

namespace aro {

namespace util {

template <class T> class Vector;

template <class T>
using RVector = Ref<Vector<T>>;

/**
 * Vector class template declaration
 */ 
template <class T>
class Vector : public AbstractList<T>
{
   public:
      Vector();
      Vector(vint capacity);
      Vector(vint capacity, vint increment);
      
      virtual vint size();
      virtual void clear();
      virtual vint capacity();
      virtual vbool isEmpty();
      virtual RArray<T> toArray();
      virtual vbool add(Ref<T> obj);
      virtual Ref<T> get(vint index);
      virtual void setSize(vint size);
      virtual vbool remove(RObject obj);
      virtual Ref<T> remove(vint index);
      virtual vint indexOf(RObject item);
      virtual vbool contains(RObject item);
      virtual vint lastIndexOf(RObject item);
      virtual void add(vint index, Ref<T> obj);
      virtual Ref<T> set(vint index, Ref<T> obj);
      virtual vint indexOf(RObject item, vint offset);
      virtual vint lastIndexOf(RObject item, vint offset);
      virtual RList<T> sublist(vint fromIndex, vint toIndex);
      
      virtual void insertElementAt(Ref<T> item, vint index);
      virtual void setElementAt(Ref<T> item, vint index);
      virtual vbool removeElement(RObject item);
      virtual void removeElementAt(vint index);
      virtual void ensureCapacity(vint min);
      virtual void addElement(Ref<T> item);
      virtual Ref<T> elementAt(vint index);
      virtual void removeAllElements();
      virtual RIterator<T> elements();
      virtual Ref<T> firstElement();
      virtual Ref<T> lastElement();
      virtual void trimToSize();
   
   protected:
      vint count;
      vint increment;
      RArray<T> data;
      
      virtual void removeRange(vint fromIndex, vint toIndex);
   
   private:
      void ensureCapacityHelper(vint min);
};


// Vector class template implementation

template <class T>
Vector<T>::Vector()
{
   count = increment = 0;
   data = new Array<T>(10);
}

template <class T>
Vector<T>::Vector(vint capacity)
{
   if(capacity < 0)
      ex_throw new ArgumentException("Illegal Capacity: " +
                                  String::valueOf(capacity));
   
   count = increment = 0;
   data = new Array<T>(capacity);
}

template <class T>
Vector<T>::Vector(vint capacity, vint increment)
{
   if(capacity < 0)
      ex_throw new ArgumentException("Illegal Capacity: " +
                                  String::valueOf(capacity));
   
   count = 0;
   thisref->increment = increment;
   data = new Array<T>(capacity);
}

template <class T>
vint Vector<T>::size()
{
   sync_lock(thisref)
   {
      return count;
   }
}

template <class T>
void Vector<T>::trimToSize()
{
   sync_lock(thisref)
   {
      modCount++;
      
      if(count < data->length)
         data = data->copyOf(0, count);
   }
}

template <class T>
vbool Vector<T>::isEmpty()
{
   sync_lock(thisref)
   {
      //vbool b = (count == 0);
      return (count == 0);
      //return b;
   }
}

template <class T>
vint Vector<T>::capacity()
{
   sync_lock(thisref)
   {
      //vint size = data->length;
      return data->length;
      //return size;
   }
}

template <class T>
void Vector<T>::setSize(vint size)
{
   sync_lock(thisref)
   {
      modCount++;
      
      if(size > count)
         ensureCapacityHelper(size);
      else
         for(vint i=size; i<count; i++)
            data[i] = nullref;
      
      count = size;
   }
}

template <class T>
void Vector<T>::ensureCapacity(vint minCapacity)
{
   sync_lock(thisref)
   {
      modCount++;
      
      ensureCapacityHelper(minCapacity);
   }
}

template <class T>
void Vector<T>::ensureCapacityHelper(vint min)
{
   if(min > data->length)
   {
      RArray<T> temp = data;
      vint newCapacity = (increment <= 0) ?
                           (data->length * 2) :
                              (data->length+increment);
      
      if(newCapacity < min) newCapacity = min;
      
      data = new Array<T>(newCapacity);
      data->copy(0, temp, 0, count);
      
      temp = nullref;
   }
}

template <class T>
vint Vector<T>::indexOf(RObject obj)
{
   return indexOf(obj, 0);
}

template <class T>
vint Vector<T>::indexOf(RObject obj, vint offset)
{
   sync_lock(thisref)
   {
      if(obj == nullref)
      {
         for(vint i=offset; i<count; i++)
         {
            if(data[i] == nullref)
               return i;
         }
      }
      else
      {
         for(vint i=offset; i<count; i++)
         {
            if(obj->equals(data[i]))
               return i;
         }
      }
      
      return -1;
   }
}

template <class T>
vint Vector<T>::lastIndexOf(RObject obj)
{
   return lastIndexOf(obj, count-1);
}

template <class T>
vint Vector<T>::lastIndexOf(RObject obj, vint offset)
{
   sync_lock(thisref)
   {
      if(offset >= count)
         ex_throw new IndexException(String::valueOf(offset) +
                  ">= " + String::valueOf(count));
      
      if(obj == nullref)
      {
         for(vint i=offset; i>=0; i--)
         {
            if(data[i] == nullref)
               return i;
         }
      }
      else
      {
         for(vint i=offset; i>=0; i--)
         {
            if(obj->equals(data[i]))
               return i;
         }
      }
      
      return -1;
   }
}

template <class T>
vbool Vector<T>::contains(RObject obj)
{
   return indexOf(obj, 0) >= 0;
}

template <class T>
Ref<T> Vector<T>::elementAt(vint index)
{
   sync_lock(thisref)
   {
      if(index >= count)
         ex_throw new IndexException(String::valueOf(index) +
                  ">= " + String::valueOf(count));
      
      return data[index];
   }
}

template <class T>
Ref<T> Vector<T>::firstElement()
{
   sync_lock(thisref)
   {
      if(count == 0)
         ex_throw new StateException("Vector is empty");
      
      return data[0];
   }
}

template <class T>
Ref<T> Vector<T>::lastElement()
{
   sync_lock(thisref)
   {
      if(count == 0)
         ex_throw new StateException("Vector is empty");
      
      return data[count-1];
   }
}

template <class T>
void Vector<T>::setElementAt(Ref<T> obj, vint index)
{
   sync_lock(thisref)
   {
      if(index >= count)
         ex_throw new IndexException(String::valueOf(index) +
                  ">= " + String::valueOf(count));
      
      data[index] = obj;
   }
}

template <class T>
void Vector<T>::removeElementAt(vint index)
{
   sync_lock(thisref)
   {
      modCount++;
      
      if(index >= count)
         ex_throw new IndexException(String::valueOf(index) +
                  ">= " + String::valueOf(count));
      
      if(index < 0)
         ex_throw new IndexException(index);
      
      vint num = count - index - 1;
      
      if(num > 0)
         data->copy(index, data, index+1, num);
      
      data[--count] = nullref; // to let gc do its work
   }
}

template <class T>
void Vector<T>::insertElementAt(Ref<T> obj, vint index)
{
   sync_lock(thisref)
   {
      modCount++;
      
      if(index >= count)
         ex_throw new IndexException(String::valueOf(index) +
                  ">= " + String::valueOf(count));
      
      ensureCapacityHelper(count+1);
      
      data->copy(index+1, data, index, count-index);
      
      data[index] = obj;
      
      count++;
   }
}

template <class T>
void Vector<T>::addElement(Ref<T> obj)
{
   sync_lock(thisref)
   {
      modCount++;
      
      ensureCapacityHelper(count+1);
      
      data[count++] = obj;
   }
}

template <class T>
vbool Vector<T>::removeElement(RObject obj)
{
   sync_lock(thisref)
   {
      modCount++;
      
      vint index = indexOf(obj, 0);
      
      if(index >= 0)
      {
         removeElementAt(index);
         
         return true;
      }
      
      return false;
   }
}

template <class T>
void Vector<T>::removeAllElements()
{
   sync_lock(thisref)
   {
      modCount++;
      
      // Let gc do its work
      for(vint i=0; i<count; i++)
         data[i] = nullref;
      
      count = 0;
   }
}

template <class T>
RArray<T> Vector<T>::toArray()
{
   sync_lock(thisref)
   {
      return data->copyOf(count);
   }
}

template <class T>
RIterator<T> Vector<T>::elements()
{
   // see java.util.Collections#getSyncIterator(Collection<T>)
   return iterator();
}

template <class T>
Ref<T> Vector<T>::get(vint index)
{
   sync_lock(thisref)
   {
      if(index >= count)
         ex_throw new IndexException(index);
      
      return data[index];
   }
}

template <class T>
Ref<T> Vector<T>::set(vint index, Ref<T> obj)
{
   sync_lock(thisref)
   {
      if(index >= count)
         ex_throw new IndexException(index);
      
      Ref<T> oldVal = data[index];
      
      data[index] = obj;
      
	  return oldVal;
   }
}

template <class T>
vbool Vector<T>::add(Ref<T> obj)
{
   sync_lock(thisref)
   {
      modCount++;
      
      ensureCapacityHelper(count+1);
      
      data[count++] = obj;
      
      return true;
   }
}

template <class T>
vbool Vector<T>::remove(RObject obj)
{
   return removeElement(obj);
}

template <class T>
void Vector<T>::add(vint index, Ref<T> obj)
{
   insertElementAt(obj, index);
}

template <class T>
Ref<T> Vector<T>::remove(vint index)
{
   sync_lock(thisref)
   {
      modCount++;
      
      if(index >= count)
         ex_throw new IndexException(index);
      
      Ref<T> oldVal = data[index];
      
      vint numMoved = count-index-1;
      
      if(numMoved > 0)
         data->copy(index, data, index+1, numMoved);
      
      data[--count] = nullref; // Let gc do its work

	  return oldVal;
   }
}

template <class T>
void Vector<T>::clear()
{
   removeAllElements();
}

template <class T>
RList<T> Vector<T>::sublist(vint fromIndex, vint toIndex)
{
   sync_lock(thisref)
   {
      // see java.util.AbstractList<T>#syncSublist(from,to)
      return AbstractList<T>::sublist(fromIndex, toIndex);
   }
}

template <class T>
void Vector<T>::removeRange(vint fromIndex, vint toIndex)
{
   sync_lock(thisref)
   {
      modCount++;
      
      vint numMoved = count - toIndex;
      
      data->copy(fromIndex, data, toIndex, numMoved);
      
      vint newCount = count - (toIndex-fromIndex);
      
      // Let gc do its work
      while(count != newCount)
          data[--count] = nullref;
   }
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_VECTOR_H */
