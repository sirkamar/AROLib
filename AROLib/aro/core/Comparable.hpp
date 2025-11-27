#ifndef CORE_COMPARABLE_H
#define CORE_COMPARABLE_H

#include <aro/core/Interface.hpp>

namespace aro {

template <class T>
using RComparable = Ref<Comparable<T>>;

template <class T>
interface Comparable extends Interface
{
   virtual vint compareTo(Ref<T> val)=0;
};

} /* namespace aro */

#endif /* CORE_COMPARABLE_H */
