#ifndef CORE_ITERABLE_H
#define CORE_ITERABLE_H

#include <aro/util/Iterator.hpp>

namespace aro {

template <class T>
interface Iterable;

template <class T>
using RIterable = Ref<Iterable<T>>;

template <class T>
interface Iterable : Interface
{
   virtual util::RIterator<T> iterator()=0;
};

} /* namespace aro */

#endif /* CORE_ITERABLE_H */
