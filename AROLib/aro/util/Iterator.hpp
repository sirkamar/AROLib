#ifndef UTIL_ITERATOR_H
#define UTIL_ITERATOR_H

#include <aro/core/Interface.hpp>

namespace aro {

namespace util {

template <class T> interface Iterator;

template <class T>
using RIterator = Ref<Iterator<T>>;

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
