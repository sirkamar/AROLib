#ifndef UTIL_LISTITERATOR_H
#define UTIL_LISTITERATOR_H

#include <aro/util/Iterator.h>

namespace aro {

namespace util {

template <class T> interface ListIterator;

template <class T>
using RListIterator = Ref<ListIterator<T>>;

template <class T>
interface ListIterator : Iterator<T>
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
