#ifndef UTIL_ARRAYLIST_H
#define UTIL_ARRAYLIST_H

#include <aro/util/AbstractList.hpp>

namespace aro {

namespace util {

template <class T> class ArrayList;

template <class T>
using RArrayList = Ref<ArrayList<T>>;

/**
 * ArrayList class template declaration
 */ 
template <class T>
class ArrayList extends public AbstractList<T>
{
   public:
      ArrayList();
      ArrayList(vint capacity);
      ArrayList(RCollection<T> c);
      
      virtual vint size();
      virtual void clear();
      virtual vbool isEmpty();
      virtual void trimToSize();
      virtual RArray<T> toArray();
      virtual vbool add(Ref<T> obj);
      virtual Ref<T> get(vint index);
      virtual Ref<T> remove(vint index);
      virtual vint indexOf(RObject obj);
      virtual vbool remove(RObject obj);
      virtual vbool contains(RObject obj);
      virtual vint lastIndexOf(RObject obj);
      virtual void ensureCapacity(vint min);
      virtual Ref<T> set(vint index, Ref<T>);
      virtual void add(vint index, Ref<T> obj);

      virtual vbool addAll(RCollection<T> c);
      virtual vbool addAll(vint index, RCollection<T> c);
   
   protected:
      virtual void removeRange(vint fromIndex, vint toIndex);
   
   private:
      vint count;
      RArray<T> data;
      
      void fastRemove(vint index);
      void rangeCheck(vint index);
};


// ArrayList class template implementation

template <class T>
ArrayList<T>::ArrayList()
   :ArrayList(10)
{
   //count = 0;
   //data = new Array<Ref<T>>(10);
}

template <class T>
ArrayList<T>::ArrayList(vint capacity)
{
   if(capacity < 0)
      ex_throw new ArgumentException("illegal capacity: "+
               String::valueOf(capacity));
   
   count = 0;
   data = new Array<T>(capacity);
}

template <class T>
ArrayList<T>::ArrayList(RCollection<T> c)
   :ArrayList(c->size())
{
   addAll(c);
}

template <class T>
void ArrayList<T>::trimToSize()
{
   modCount++;
   vint oldCapacity = data->length;
   if(count < oldCapacity)
      data = data->copyOf(count);
}

template <class T>
void ArrayList<T>::ensureCapacity(vint min)
{
   modCount++;
   vint oldCapacity = data->length;
   if(min > oldCapacity)
   {
      vint newCapacity = (oldCapacity*3)/2+1;
      if(newCapacity < min)
         newCapacity = min;
      
      data = data->copyOf(newCapacity);
   }
}

template <class T>
vint ArrayList<T>::size()
{
   return count;
}

template <class T>
vbool ArrayList<T>::isEmpty()
{
   return count == 0;
}

template <class T>
vbool ArrayList<T>::contains(RObject obj)
{
   return indexOf(obj) >= 0;
}

template <class T>
vint ArrayList<T>::indexOf(RObject obj)
{
   if(obj==nullref)
   {
      for(vint i=0; i<count; i++)
         if(data[i] == nullref)
            return i;
   }
   else
   {
      for(vint i=0; i<count; i++)
         if(obj->equals(data[i]))
            return i;
   }
   
   return -1;
}

template <class T>
vint ArrayList<T>::lastIndexOf(RObject obj)
{
   if(obj==nullref)
   {
      for(vint i=count-1; i>=0; i--)
         if(data[i] == nullref)
            return i;
   }
   else
   {
      for(vint i=count-1; i>=0; i--)
         if(obj->equals(data[i]))
            return i;
   }
   
   return -1;
}

template <class T>
Ref<T> ArrayList<T>::get(vint index)
{
   rangeCheck(index);
   
   return data[index];
}

template <class T>
Ref<T> ArrayList<T>::set(vint index, Ref<T> obj)
{
   rangeCheck(index);
   
   Ref<T> oldVal = data[index];
   data[index] = obj;
   return oldVal;
}

template <class T>
vbool ArrayList<T>::add(Ref<T> obj)
{
   ensureCapacity(count+1);
   data[count++] = obj;
   return true;
}

template <class T>
void ArrayList<T>::add(vint index, Ref<T> obj)
{
   if(index<0 || index > count)
      ex_throw new IndexException("Index: "+String::valueOf(index)+
               ", Size: "+String::valueOf(count));
   
   ensureCapacity(count+1);
   data->copy(index+1, data, index, count-index);
   data[index] = obj;
   count++;
}

template <class T>
Ref<T> ArrayList<T>::remove(vint index)
{
   rangeCheck(index);
   
   modCount++;
   Ref<T> oldVal = data[index];
   vint numMoved = count-index-1;
   if(numMoved > 0)
      data->copy(index, data, index+1, numMoved);
   data[--count] = nullref; // Let gc do its work
   return oldVal;
}

template <class T>
vbool ArrayList<T>::remove(RObject obj)
{
   if(obj == nullref)
   {
      for(vint index=0; index<count; index++)
         if(data[index] == nullref)
         {
            fastRemove(index);
            return true;
         }
   }
   else
   {
      for(vint index=0; index<count; index++)
         if(obj->equals(data[index]))
         {
            fastRemove(index);
            return true;
         }
   }
   
   return false;
}

template <class T>
RArray<T> ArrayList<T>::toArray()
{
   return data->copyOf(count);
}

template <class T>
void ArrayList<T>::clear()
{
   modCount++;
   
   // Let gc do its work
   for(vint i=0; i<count; i++)
      data[i] = nullref;
   
   count = 0;
}

template <class T>
vbool ArrayList<T>::addAll(RCollection<T> c)
{
   return addAll(count, c);
   //RArray<Ref<T>> a = c->toArray();
   //vint newNum = a->length;
   //
   //ensureCapacity(count + newNum);
   //
   //data->copy(count, a, 0, newNum);
   //
   //count += newNum;
   //
   //return newNum != 0;
}

template <class T>
vbool ArrayList<T>::addAll(vint index, RCollection<T> c)
{
   if(index<0 || index > count)
      ex_throw new IndexException("Index: "+String::valueOf(index)+
               ", Size: "+String::valueOf(count));
   
   RArray<T> a = c->toArray();
   vint numNew = a->length;
   ensureCapacity(count + numNew);  // Increments modCount
   
   vint numMoved = count - index;
   if(numMoved > 0)
      data->copy(index+numNew, data, index, numMoved);
   
   data->copy(index, a, 0, numNew);
   count += numNew;
   return numNew != 0;
}

template <class T>
void ArrayList<T>::removeRange(vint fromIndex, vint toIndex)
{
   modCount++;
   vint numMoved = count-toIndex;
   data->copy(fromIndex, data, toIndex, numMoved);
   
   // Let gc do its work
   vint newSize = count - (toIndex-fromIndex);
   while(count != newSize)
      data[--count] = nullref;
}

template <class T>
void ArrayList<T>::fastRemove(vint index)
{
   modCount++;
   vint numMoved = count-index-1;
   if(numMoved > 0)
      data->copy(index, data, index+1, numMoved);
   data[--count] = nullref; // Let gc do its work
}

template <class T>
void ArrayList<T>::rangeCheck(vint index)
{
   if(index >= count)
      ex_throw new IndexException("Index: "+String::valueOf(index)+
               ", Size: "+String::valueOf(count));
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_ARRAYLIST_H */
