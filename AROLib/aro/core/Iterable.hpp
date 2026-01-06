#ifndef CORE_ITERABLE_H
#define CORE_ITERABLE_H

#include <aro/util/Iterator.hpp>

namespace aro {

template <class T>
interface Iterable;

template <class T>
using RIterable = Ref<Iterable<T>>;

/*
 Implementing this interface allows an object to be
 the target of the "range-based for" statement, or
 the aro::for_each utility.
*/
template <class T>
interface Iterable extends Interface
{
   virtual util::RIterator<T> iterator()=0;
};

} /* namespace aro */

#endif /* CORE_ITERABLE_H */
