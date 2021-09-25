#ifndef UTIL_SET_H
#define UTIL_SET_H

#include <aro/util/Collection.h>

namespace aro {

namespace util {

template <class T> interface Set;

template <class T>
using RSet = Ref<Set<T>>;

template <class T>
interface Set : virtual Collection<T>
{
   virtual vint size()=0;
   virtual void clear()=0;
   virtual vbool isEmpty()=0;
   virtual RArray<T> toArray()=0;
   virtual vbool add(Ref<T> e)=0;
   virtual RIterator<T> iterator()=0;
   virtual vbool remove(RObject o)=0;
   virtual vbool contains(RObject o)=0;
   virtual vbool addAll(RCollection<T> c)=0;
   virtual vbool removeAll(RCollection<T> c)=0;
   virtual vbool containsAll(RCollection<T> c)=0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_SET_H */
