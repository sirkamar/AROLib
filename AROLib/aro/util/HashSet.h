#ifndef UTIL_HASHSET_H
#define UTIL_HASHSET_H

#include <aro/util/HashMap.h>

namespace aro {

namespace util {

template <class T> class HashSet;

template <class T>
using RHashSet = Ref<HashSet<T>>;

/**
 * HashSet class template declaration
 */ 
template <class T>
class HashSet : public AbstractSet<T>
{
   public:
      HashSet();
      HashSet(RCollection<T> c);
      HashSet(vint initialCapacity);
      HashSet(vint initialCapacity, vfloat loadFactor);

      virtual vbool contains(RObject o);
      virtual RIterator<T> iterator();
      virtual vbool remove(RObject o);
      virtual vbool add(Ref<T> t);
      virtual vbool isEmpty();
      virtual void clear();
      virtual vint size();

   private:
      RHashMap<T, Object> map;
      static const RObject PRESENT;
};


// HashSet class template implementation

template <class T>
const RObject HashSet<T>::PRESENT = new Object();

template <class T>
HashSet<T>::HashSet()
{
   map = new HashMap<T, Object>();
}

template <class T>
HashSet<T>::HashSet(RCollection<T> c)
{
   map = new HashMap<T, Object>(Math::maximum((vint) (c->size()/0.75f)+1, 16));

   addAll(c);
}

template <class T>
HashSet<T>::HashSet(vint initialCapacity)
{
   map = new HashMap<T, Object>(initialCapacity);
}

template <class T>
HashSet<T>::HashSet(vint initialCapacity, vfloat loadFactor)
{
   map = new HashMap<T, Object>(initialCapacity, loadFactor);
}

template <class T>
RIterator<T> HashSet<T>::iterator()
{
   return map->keySet()->iterator();
}

template <class T>
vint HashSet<T>::size()
{
   return map->size();
}

template <class T>
vbool HashSet<T>::isEmpty()
{
   return map->isEmpty();
}

template <class T>
vbool HashSet<T>::contains(RObject o)
{
   return map->containsKey(o);
}

template <class T>
vbool HashSet<T>::add(Ref<T> t)
{
   return map->put(t, PRESENT) == nullref;
}

template <class T>
vbool HashSet<T>::remove(RObject o)
{
   return map->remove(o) == PRESENT;
}

template <class T>
void HashSet<T>::clear()
{
   map->clear();
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_HASHSET_H */
