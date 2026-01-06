#ifndef UTIL_LISTITERATOR_H
#define UTIL_LISTITERATOR_H

#include <aro/util/Iterator.hpp>

namespace aro {

namespace util {

template <class T> interface ListIterator;

template <class T>
using RListIterator = Ref<ListIterator<T>>;

/**
 An iterator for lists that allows the programmer
 to traverse the list in either direction, modify
 the list during iteration, and obtain the iterator's
 current position in the list. A ListIterator has no
 current element; its 'cursor position' always lies
 between the element that would be returned by a call
 to previous() and the element that would be returned
 by a call to next().

Note that the remove() and set(RObject) methods are <em>not</em>
defined in terms of the cursor position; they are defined to
operate on the last element returned by a call to next() or
previous().

This interface is a member of the AROLib Collections Framework.
*/
template <class T>
interface ListIterator extends Iterator<T>
{
   virtual Ref<T> next() = 0;
   virtual void remove() = 0;
   virtual vbool hasNext() = 0;
   virtual vint nextIndex() = 0;
   virtual Ref<T> previous() = 0;
   virtual vbool hasPrevious() = 0;
   virtual void add(Ref<T> obj) = 0;
   virtual void set(Ref<T> obj) = 0;
   virtual vint previousIndex() = 0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_LISTITERATOR_H */
