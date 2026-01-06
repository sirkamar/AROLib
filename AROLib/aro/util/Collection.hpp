#ifndef UTIL_COLLECTION_H
#define UTIL_COLLECTION_H

#include <aro/core.hpp>

namespace aro {

namespace util {

template <class T> interface Collection;

template <class T>
using RCollection = Ref<Collection<T>>;

/*
 Collection is the root interface in the "collection hierarchy".
 A collection represents a group of objects, known as its elements.
 Some collections allow duplicate elements and others do not. Some
 are ordered and others unordered. The AROLib does not provide any
 direct implementations of this interface, however, it does provide
 implementations of more specific subinterfaces like "Set" and "List".
 This interface is typically used to pass around and manipulate
 collections where maximum generality is desired.

 This interface is a member of the AROLib Collections Framework.
*/
template <class T>
interface Collection extends Iterable<T>
{
   virtual vint size() = 0;
   virtual void clear() = 0;
   //virtual vint hashCode() = 0;
   virtual vbool isEmpty() = 0;
   virtual RArray<T> toArray() = 0;
   virtual vbool add(Ref<T> e) = 0;
   virtual RIterator<T> iterator() = 0;
   virtual vbool remove(RObject o) = 0;
   //virtual vbool equals(RObject o) = 0;
   virtual vbool contains(RObject o) = 0;
   virtual vbool addAll(RCollection<T> c) = 0;
   virtual vbool removeAll(RCollection<T> c) = 0;
   virtual vbool containsAll(RCollection<T> c) = 0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_COLLECTION_H */
