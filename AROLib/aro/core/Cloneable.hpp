#ifndef CORE_CLONEABLE_H
#define CORE_CLONEABLE_H

#include <aro/core/Object.hpp>

namespace aro {

template <class T>
interface Cloneable;

template <class T>
using RCloneable = Ref<Cloneable<T>>;

template <class T>
interface Cloneable extends Interface
{
   private:
      static vbool dummy;

   protected:
      Cloneable();
};

} /* namespace aro */

#endif /* CORE_CLONEABLE_H */
