#ifndef UTIL_COMPARATOR_H
#define UTIL_COMPARATOR_H

#include <aro/core.hpp>

namespace aro {

namespace util {

template <class T> interface Comparator;

template <class T>
using RComparator = Ref<Comparator<T>>;

/*
 Provides a comparison function, which imposes a "total ordering" on some
 collection of objects. Comparators can be passed to a sort method to allow
 precise control over the sort order. Comparators can also be used to control
 the order of certain data structures or to provide an ordering for collections
 of objects that don't have a Comparable based natural ordering.

 This interface is a member of the AROLib Collections Framework.
*/
template <class T>
interface Comparator extends Interface
{
   virtual vint compareTo(Ref<T> item1, Ref<T> item2)=0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_COMPARATOR_H */
