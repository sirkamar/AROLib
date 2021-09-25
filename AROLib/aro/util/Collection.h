#ifndef UTIL_COLLECTION_H
#define UTIL_COLLECTION_H

#include <aro/core.h>

namespace aro {

namespace util {

template <class T> interface Collection;

template <class T>
using RCollection = Ref<Collection<T>>;

template <class T>
interface Collection : Iterable<T>
{
   virtual vint size() = 0;
   virtual void clear() = 0;
   virtual vbool isEmpty() = 0;
   virtual RArray<T> toArray() = 0;
   virtual vbool add(Ref<T> e) = 0;
   virtual vbool remove(RObject o) = 0;
   virtual RIterator<T> iterator() = 0;
   virtual vbool contains(RObject o) = 0;
   virtual vbool addAll(RCollection<T> c) = 0;
   virtual vbool removeAll(RCollection<T> c) = 0;
   virtual vbool containsAll(RCollection<T> c) = 0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_COLLECTION_H */
