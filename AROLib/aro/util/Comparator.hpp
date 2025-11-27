#ifndef UTIL_COMPARATOR_H
#define UTIL_COMPARATOR_H

#include <aro/core.hpp>

namespace aro {

namespace util {

template <class T> interface Comparator;

template <class T>
using RComparator = Ref<Comparator<T>>;

template <class T>
interface Comparator extends Interface
{
   virtual vint compareTo(Ref<T> item1, Ref<T> item2)=0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_COMPARATOR_H */
