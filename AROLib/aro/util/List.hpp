#ifndef UTIL_LIST_H
#define UTIL_LIST_H

#include <aro/util/Collection.hpp>
#include <aro/util/ListIterator.hpp>

namespace aro {

namespace util {

template <class T> interface List;

template <class T>
using RList = Ref<List<T>>;

template <class T>
interface List : virtual Collection<T>
{
   // from Collection
   virtual vint size() = 0;
   virtual void clear() = 0;
   virtual vint hashCode() = 0;
   virtual vbool isEmpty() = 0;
   virtual RArray<T> toArray() = 0;
   virtual vbool add(Ref<T> obj) = 0;
   virtual vbool equals(RObject o) = 0;
   virtual vbool remove(RObject o) = 0;
   virtual RIterator<T> iterator() = 0;
   virtual vbool contains(RObject o) = 0;
   virtual vbool addAll(RCollection<T> c) = 0;
   virtual vbool removeAll(RCollection<T> c) = 0;
   virtual vbool containsAll(RCollection<T> c) = 0;
   
   // List specific
   virtual Ref<T> get(vint index) = 0;
   virtual Ref<T> remove(vint index) = 0;
   virtual vint indexOf(RObject obj) = 0;
   virtual vint lastIndexOf(RObject obj) = 0;
   virtual RListIterator<T> listIterator() = 0;
   virtual void add(vint index, Ref<T> obj) = 0;
   virtual Ref<T> set(vint index, Ref<T> obj) = 0;
   virtual RListIterator<T> listIterator(vint index) = 0;
   virtual vbool addAll(vint index, RCollection<T> c) = 0;
   virtual RList<T> sublist(vint fromIndex, vint toIndex) = 0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_LIST_H */
