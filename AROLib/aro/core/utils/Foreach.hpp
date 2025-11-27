#ifndef CORE_FOREACH_H
#define CORE_FOREACH_H

#include <aro/core/impl/Array2D-impl.hpp>

namespace aro {

template <class T, class U>
void for_each(T collection, U execute)
{
   for(auto element : collection)
      execute(element);
}

} /* namespace aro */

#endif /* CORE_FOREACH_H */
