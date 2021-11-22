#ifndef CORE_FOREACH_H
#define CORE_FOREACH_H

#include <aro/core/Iterable.hpp>
#include <aro/core/Array2D-impl.hpp>

namespace aro {

template <class T>
inline void for_each(RArray<T> array, std::function<void(Ref<T>)> execute)
{
   for(int n=0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vint> array, std::function<void(vint)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vbool> array, std::function<void(vbool)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vchar> array, std::function<void(vchar)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vlong> array, std::function<void(vlong)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vshort> array, std::function<void(vshort)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vfloat> array, std::function<void(vfloat)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

inline void for_each(RArray<vdouble> array, std::function<void(vdouble)> execute)
{
   for(int n = 0; n<array->length; n++)
      execute(array[n]);
}

template <class T>
inline void for_each(RIterable<T> collection, std::function<void(Ref<T>)> execute)
{
   util::RIterator<T> iterator = collection->iterator();
   
   while(iterator->hasNext())
      execute(iterator->next());
}

template <class T, class U>
inline void for_each(T collection, U execute)
{
   auto iterator = collection->iterator();

   while(iterator->hasNext())
      execute(iterator->next());
}

} /* namespace aro */

#endif /* CORE_FOREACH_H */
