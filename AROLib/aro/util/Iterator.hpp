#ifndef UTIL_ITERATOR_H
#define UTIL_ITERATOR_H

#include <aro/core/Interface.hpp>

namespace aro {

namespace util {

template <class T> interface Iterator;

template <class T>
using RIterator = Ref<Iterator<T>>;

/*
 This interface represents an iterator over a collection.
 An iterator takes the place of a cursor in a collection
 of elements.

 This interface is a member of the AROLib Collections Framework.
*/
template <class T>
interface Iterator extends Interface
{
   virtual vbool hasNext() = 0;
   virtual Ref<T> next() = 0;
   virtual void remove() = 0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_ITERATOR_H */
