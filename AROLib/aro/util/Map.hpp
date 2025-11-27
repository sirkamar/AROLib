#ifndef UTIL_MAP_H
#define UTIL_MAP_H

#include <aro/util/Set.hpp>

namespace aro {

namespace util {

template <class K, class V> interface Map;

template <class K, class V>
using RMap = Ref<Map<K,V>>;

template <class K, class V>
interface Map extends Interface
{
   interface Node;
   typedef Ref<Node> RNode;
   
   interface Node : Interface
   {
      virtual Ref<K> getKey()=0;
      virtual Ref<V> getValue()=0;
      virtual Ref<V> setValue(Ref<V> val)=0;
   };
   
   virtual vint size()=0;
   virtual void clear()=0;
   virtual vint hashCode()=0;
   virtual vbool isEmpty()=0;
   virtual RSet<K> keySet()=0;
   virtual RSet<Node> nodeSet()=0;
   virtual RCollection<V> values()=0;
   virtual Ref<V> get(RObject key)=0;
   virtual vbool equals(RObject obj)=0;
   virtual Ref<V> remove(RObject key)=0;
   virtual void putAll(RMap<K,V> map)=0;
   virtual vbool containsKey(RObject key)=0;
   virtual vbool containsValue(RObject val)=0;
   virtual Ref<V> put(Ref<K> key, Ref<V> val)=0;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_MAP_H */
