#ifndef UTIL_SET_H
#define UTIL_SET_H

#include <aro/util/Collection.hpp>

namespace aro {

namespace util {

template <class T> interface Set;

template <class T>
using RSet = Ref<Set<T>>;

/*
 A Set is a collection that contains no duplicate elements,
 and at most one null element.  As implied by its name, this
 interface models the mathematical set abstraction.

 This interface is a member of the AROLib Collections Framework.
*/
template <class T>
interface Set extends virtual Collection<T>
{
   virtual vint size()=0;
   virtual void clear()=0;
   virtual vint hashCode()=0;
   virtual vbool isEmpty()=0;
   virtual RArray<T> toArray()=0;
   virtual vbool add(Ref<T> e)=0;
   virtual RIterator<T> iterator()=0;
   virtual vbool equals(RObject o)=0;
   virtual vbool remove(RObject o)=0;
   virtual vbool contains(RObject o)=0;
   virtual vbool addAll(RCollection<T> c)=0;
   virtual vbool removeAll(RCollection<T> c)=0;
   virtual vbool containsAll(RCollection<T> c)=0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_SET_H */
