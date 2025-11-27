#ifndef UTIL_WEAKHASHMAP_H
#define UTIL_WEAKHASHMAP_H

#include <aro/util/AbstractMap.hpp>

namespace aro {

namespace util {

template <class K, class V> class WeakHashMap;

template <class K, class V>
using RWeakHashMap = Ref<WeakHashMap<K,V>>;

/**
 * WeakHashMap class template declaration
 */ 
template <class K, class V>
class WeakHashMap extends public AbstractMap<K,V>
{
   public:
      class Node;
      typedef Ref<Node> RNode;
      
      class Node : public Weak<K>, public Map<K,V>::Node
      {
         public:
            Node(Ref<K> k, Ref<V> v, vint h, RNode n, RWeakHashMap<K,V> m);
            
            virtual Ref<V> setValue(Ref<V> newValue);
            virtual vbool equals(RObject o);
            virtual RString toString();
            virtual Ref<V> getValue();
            virtual Ref<K> getKey();
            virtual vint hashCode();

         private:
            RNode next;
            Ref<V> value;
            const vint hash;
            RWeakHashMap<K,V> map;
         
         friend class WeakHashMap<K,V>;
      };
      
      WeakHashMap();
      WeakHashMap(RMap<K,V> map);
      WeakHashMap(vint initialCapacity);
      WeakHashMap(vint initialCapacity, vfloat loadFactor);
      
      virtual vint size();
      virtual void clear();
      virtual vbool isEmpty();
      virtual Ref<V> get(RObject key);
      virtual Ref<V> remove(RObject key);
      virtual void putAll(RMap<K,V> map);
      virtual vbool containsKey(RObject key);
      virtual vbool containsValue(RObject value);
      virtual Ref<V> put(Ref<K> key, Ref<V> value);

      virtual RSet<K> keySet();
      virtual RCollection<V> values();
      virtual RSet<Map<K,V>::Node> nodeSet();
   
   protected:
      RArray<Node> getTable();
      static vint hash(vint h);
      RNode getNode(RObject key);
      void resize(vint newCapacity);
      RNode removeMapping(RObject obj);
      static vint indexFor(vint h, vint length);
      void transfer(RArray<Node> src, RArray<Node> dest);
      
      virtual RIterator<K> newKeyIterator();
      virtual RIterator<V> newValueIterator();
      virtual RIterator<Map<K,V>::Node> newNodeIterator();
   
   private:
      vint count;
      vint threshold;
      RArray<Node> table;
      volatile vint modCount;
      const vfloat loadFactor;
      RSet<Map<K,V>::Node> theNodeSet;
      
      void expungeStaleNodes();
      vbool containsNullValue();
      static RObject maskNull(RObject key);
      static Ref<K> unmaskNull(RObject key);
      static vbool eq(RObject x, RObject y);
      
      static const RObject NULL_KEY;
      static const vint MAXIMUM_CAPACITY;
      static const vfloat DEFAULT_LOAD_FACTOR;
      static const vint DEFAULT_INITIAL_CAPACITY;
      
      template <class T>
      class HashIterator : public Object, public Iterator<T>
      {
         public:
            HashIterator(RWeakHashMap<K,V> m);
            
            RNode nextNode();
            virtual void remove();
            virtual vbool hasNext();
         
         private:
            vint index;
            RNode node;
            RObject nextKey;
            RObject currentKey;
            RNode lastReturned;
            RWeakHashMap<K,V> map;
            vint expectedModCount;
      };

      class KeyIterator : public HashIterator<K>
      {
         public:
            KeyIterator(RWeakHashMap<K,V> m);
            virtual Ref<K> next();
      };

      class ValueIterator : public HashIterator<V>
      {
         public:
            ValueIterator(RWeakHashMap<K,V> m);
            virtual Ref<V> next();
      };

      class NodeIterator : public HashIterator<Map<K,V>::Node>
      {
         public:
            NodeIterator(RWeakHashMap<K,V> m);
            virtual Map<K,V>::RNode next();
      };

      class KeySet : public AbstractSet<K>
      {
         public:
            KeySet(RWeakHashMap<K,V> map);
            
            vbool contains(RObject o);
            RIterator<K> iterator();
            vbool remove(RObject o);
            void clear();
            vint size();
         
         private:
            RWeakHashMap<K,V> map;
      };

      class Values : public AbstractCollection<V>
      {
         public:
            Values(RWeakHashMap<K,V> map);
            
            vbool contains(RObject o);
            RIterator<V> iterator();
            void clear();
            vint size();
         
         private:
            RWeakHashMap<K,V> map;
      };
      
      class NodeSet : public AbstractSet<Map<K,V>::Node>
      {
         public:
            NodeSet(RWeakHashMap<K,V> map);
            
            RIterator<Map<K,V>::Node> iterator();
            RArray<Map<K,V>::Node> toArray();
            vbool contains(RObject o);
            vbool remove(RObject o);
            void clear();
            vint size();
         
         private:
            RWeakHashMap<K,V> map;
      };
};


// WeakHashMap class template implementation

template <class K, class V>
const RObject WeakHashMap<K,V>::NULL_KEY = new Object();

template <class K, class V>
const vint WeakHashMap<K,V>::MAXIMUM_CAPACITY = 1 << 30;

template <class K, class V>
const vint WeakHashMap<K,V>::DEFAULT_INITIAL_CAPACITY = 16;

template <class K, class V>
const vfloat WeakHashMap<K,V>::DEFAULT_LOAD_FACTOR = 0.75f;

template <class K, class V>
WeakHashMap<K,V>::WeakHashMap()
   :loadFactor(DEFAULT_LOAD_FACTOR)
{
   modCount = 0;
   threshold = (vint) DEFAULT_INITIAL_CAPACITY * loadFactor;

   table = new Array<Node>(DEFAULT_INITIAL_CAPACITY);
}

template <class K, class V>
WeakHashMap<K,V>::WeakHashMap(RMap<K,V> m)
   :HashMap<K, V>(m), loadFactor(DEFAULT_LOAD_FACTOR)
{
   vint capacity = Math::maximum((vint) (m->size() / DEFAULT_LOAD_FACTOR) + 1,
                              DEFAULT_INITIAL_CAPACITY);
   
   modCount = 0;
   threshold = (vint) capacity * loadFactor;
   
   table = new Array<Node>(capacity);
   
   putAll(m);
}

template <class K, class V>
WeakHashMap<K,V>::WeakHashMap(vint initialCapacity)
:HashMap<K, V>(initialCapacity), loadFactor(DEFAULT_LOAD_FACTOR)
{
   if(initialCapacity < 0)
      ex_throw new ArgumentException("Illegal initial capacity:" +
                                    String::valueOf(initialCapacity));

   if(initialCapacity > MAXIMUM_CAPACITY)
      initialCapacity = MAXIMUM_CAPACITY;

   // Find a power of 2 >= initialCapacity
   vint capacity = 1;
   while(capacity < initialCapacity)
      capacity <<= 1;
   
   modCount = 0;
   threshold = (vint) capacity * loadFactor;

   table = new Array<Node>(capacity);
}

template <class K, class V>
WeakHashMap<K,V>::WeakHashMap(vint initialCapacity, vfloat loadFactor)
   :HashMap<K, V>(initialCapacity, loadFactor), loadFactor(loadFactor)
{
   if(initialCapacity < 0)
      ex_throw new ArgumentException("Illegal initial capacity:" +
                                    String::valueOf(initialCapacity));

   if(initialCapacity > MAXIMUM_CAPACITY)
      initialCapacity = MAXIMUM_CAPACITY;

   if(loadFactor <= 0.0f)
      ex_throw new ArgumentException("Illegal load factor:" +
                                    String::valueOf(loadFactor));

   // Find a power of 2 >= initialCapacity
   vint capacity = 1;
   while(capacity < initialCapacity)
      capacity <<= 1;

   modCount = 0;
   
   threshold = (vint) capacity * loadFactor;

   table = new Array<Node>(capacity);
}

template <class K, class V>
RObject WeakHashMap<K,V>::maskNull(RObject key)
{
   return (key == nullref ? NULL_KEY : key);
}

template <class K, class V>
Ref<K> WeakHashMap<K,V>::unmaskNull(RObject key)
{
   return type_cast<K>((key == NULL_KEY) ? nullref : key);
}

template <class K, class V>
vbool WeakHashMap<K,V>::eq(RObject x, RObject y)
{
   return x == y || x->equals(y);
}

template <class K, class V>
vint WeakHashMap<K,V>::indexFor(vint h, vint length)
{
   return h & (length-1);
}

template <class K, class V>
void WeakHashMap<K,V>::expungeStaleNodes()
{
   for(int n=0; n<table->length; n++)
   {
      RNode prev=table[n];
      RNode node=prev;

      while(node != nullref)
      {
         RNode next = node->next;
         
         // if the key was deleted by GC
         if(node->get() == nullref)
         {
            if(node == table[n])
               table[n] = next;
            else
               prev->next = next;
            
            node->next = nullref;
            node->value = nullref;
            count--;
         }
         else
            prev = node;
         
         node = next;
      }
   }
}

template <class K, class V>
RArray<typename WeakHashMap<K,V>::Node> WeakHashMap<K,V>::getTable()
{
   expungeStaleNodes();
   
   return table;
}

template <class K, class V>
vint WeakHashMap<K,V>::size()
{
   if(count == 0)
      return 0;
   
   expungeStaleNodes();
   
   return count;
}

template <class K, class V>
vbool WeakHashMap<K,V>::isEmpty()
{
   return size() == 0;
}

template <class K, class V>
vint WeakHashMap<K,V>::hash(vint h)
{
   //h ^= (h >>> 20) ^ (h >>> 12);
   //return h ^ (h >>> 7) ^ (h >>> 4);
   
   h ^= Int::urShift(h, 20) ^ Int::urShift(h, 12);
   
   return h ^ Int::urShift(h, 7) ^ Int::urShift(h, 4);
}

template <class K, class V>
Ref<V> WeakHashMap<K,V>::get(RObject key)
{
   RObject k = maskNull(key);
   vint h = hash(k->hashCode());
   RArray<Node> tab = getTable();
   vint index = indexFor(h, tab->length);
   
   RNode n = tab[index];
   while(n != nullref)
   {
      if(n->hash == h && eq(k, n->get()))
         return n->value;

      n = n->next;
   }

   return nullref;
}

template <class K, class V>
vbool WeakHashMap<K,V>::containsKey(RObject key)
{
   return (getNode(key) != nullref);
}

template <class K, class V>
typename WeakHashMap<K,V>::RNode WeakHashMap<K,V>::getNode(RObject key)
{
   RObject k = maskNull(key);
   vint h = hash(k->hashCode());
   RArray<Node> tab = getTable();
   vint index = indexFor(h, tab->length);
   
   RNode n = tab[index];
   while (n != nullref && !(n->hash == h && eq(k, n->get())))
      n = n->next;

   return n;
}

template <class K, class V>
Ref<V> WeakHashMap<K,V>::put(Ref<K> key, Ref<V> value)
{
   Ref<K> k = type_cast<K>(maskNull(key));
   vint h = hash(k->hashCode());
   RArray<Node> tab = getTable();
   vint i = indexFor(h, tab->length);

   for(RNode n=tab[i]; n!=nullref; n=n->next)
   {
      if(h == n->hash && eq(k, n->get()))
      {
         Ref<V> oldValue = n->value;

         if(value != oldValue)
            n->value = value;
         
         return oldValue;
      }
   }

   modCount++;

   RNode n = tab[i];
   tab[i] = new Node(k, value, h, n, thisref);

   if(++count >= threshold)
      resize(tab->length * 2);

   return nullref;
}

template <class K, class V>
void WeakHashMap<K,V>::resize(int newCapacity)
{
   RArray<Node> oldTable = table;
   vint oldCapacity = oldTable->length;
   if(oldCapacity == MAXIMUM_CAPACITY)
   {
      threshold = Int::MAX_VALUE;
      return;
   }

   RArray<Node> newTable = new Array<Node>(newCapacity);
   transfer(oldTable, newTable);
   table = newTable;

   /*
   * If ignoring null elements and processing deleted references caused massive
   * shrinkage, then restore old table.  This should be rare, but avoids
   * unbounded expansion of garbage-filled tables.
   */
   if(count >= threshold / 2)
      threshold = static_cast<vint>(newCapacity * loadFactor);
   else
   {
      expungeStaleNodes();
      transfer(newTable, oldTable);
      table = oldTable;
   }
}

template <class K, class V>
void WeakHashMap<K,V>::transfer(RArray<typename WeakHashMap<K,V>::Node> src, RArray<typename WeakHashMap<K,V>::Node> dest)
{
   for(int j = 0; j < src->length; ++j)
   {
      RNode n = src[j];
      src[j] = nullref;
      while(n != nullref)
      {
         RNode next = n->next;
         RObject key = n->get();

         if(key == nullref)
         {
            n->next = nullref;
            n->value = nullref;
            count--;
         }
         else
         {
            vint i = indexFor(n->hash, dest->length);
            n->next = dest[i];
            dest[i] = n;
         }

         n = next;
      }
   }
}

template <class K, class V>
void WeakHashMap<K,V>::putAll(RMap<K,V> m)
{
   vint numKeysToBeAdded = m->size();
   if(numKeysToBeAdded == 0)
      return;

   /*
   * Expand the map if the map if the number of mappings to be added
   * is greater than or equal to threshold.  This is conservative; the
   * obvious condition is (m.size() + size) >= threshold, but this
   * condition could result in a map with twice the appropriate capacity,
   * if the keys to be added overlap with the keys already in this map.
   * By using the conservative calculation, we subject ourself
   * to at most one extra resize.
   */
   if(numKeysToBeAdded > threshold)
   {
      vint targetCapacity = static_cast<vint>(numKeysToBeAdded/loadFactor+1);
      if(targetCapacity > MAXIMUM_CAPACITY)
         targetCapacity = MAXIMUM_CAPACITY;
      vint newCapacity = table->length;
      while(newCapacity < targetCapacity)
         newCapacity <<= 1;
      if(newCapacity > table->length)
         resize(newCapacity);
   }
   
   RIterator<Map<K,V>::Node> it = m->nodeSet()->iterator();
   
   while(it->hasNext())
   {
      Map<K,V>::RNode n = it->next();
      
      put(n->getKey(), n->getValue());
   }
}

template <class K, class V>
Ref<V> WeakHashMap<K,V>::remove(RObject key)
{
   RObject k = maskNull(key);
   vint h = hash(k->hashCode());
   RArray<Node> tab = getTable();
   vint i = indexFor(h, tab->length);
   
   RNode prev = tab[i];
   RNode n = prev;

   while(n != nullref)
   {
      RNode next = n->next;
      if(h == n->hash && eq(k, n->get()))
      {
         modCount++;
         count++;
         if(prev == n)
            tab[i] = next;
         else
            prev->next = next;

         return n->value;
      }

      prev = n;
      n = next;
   }

   return nullref;
}

template <class K, class V>
typename WeakHashMap<K,V>::RNode WeakHashMap<K,V>::removeMapping(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return nullref;
   
   RArray<Node> tab = getTable();
   Map<K,V>::RNode node = type_cast<typename Map<K,V>::Node>(o);
   RObject k = maskNull(node->getKey());
   vint h = hash(k->hashCode());
   vint i = indexFor(h, tab->length);
   RNode prev = tab[i];
   RNode n = prev;

   while(n != nullref)
   {
      RNode next = n->next;
      if(h == n->hash && n->equals(node))
      {
         modCount++;
         count--;
         if(prev == n)
            tab[i] = next;
         else
            prev->next = next;

         return n;
      }

      prev = n;
      n = next;
   }

   return nullref;
}

template <class K, class V>
void WeakHashMap<K,V>::clear()
{
   modCount++;

   RArray<Node> tab = table;
   for(vint i=0; i<tab->length; i++)
      tab[i] = nullref;
   count = 0;
}

template <class K, class V>
vbool WeakHashMap<K,V>::containsValue(RObject value)
{
   if(value == nullref)
      return containsNullValue();
   
   RArray<Node> tab = getTable();
   for(vint i=tab->length; i-- > 0;)
   {
      for(RNode n = tab[i]; n != nullref; n = n->next)
      {
         if(value->equals(n->value))
            return true;
      }
   }
   
   return false;
}

template <class K, class V>
vbool WeakHashMap<K,V>::containsNullValue()
{
   RArray<Node> tab = getTable();
   for(vint i=tab->length; i-- > 0;)
   {
      for(RNode n = tab[i]; n != nullref; n = n->next)
      {
         if(n->value == nullref)
            return true;
      }
   }
   
   return false;
}

template <class K, class V>
WeakHashMap<K,V>::Node::Node(Ref<K> k, Ref<V> v, vint h,
   typename WeakHashMap<K,V>::RNode n, RWeakHashMap<K,V> m)
   :Weak(k), hash(h), map(m)
{
   value = v;
   next = n;
}

template <class K, class V>
Ref<K> WeakHashMap<K,V>::Node::getKey()
{
   return map->unmaskNull(get());
}

template <class K, class V>
Ref<V> WeakHashMap<K,V>::Node::getValue()
{
   return value;
}

template <class K, class V>
Ref<V> WeakHashMap<K,V>::Node::setValue(Ref<V> newValue)
{
   Ref<V> oldValue = value;
   value = newValue;
   return oldValue;
}


template <class K, class V>
vbool WeakHashMap<K,V>::Node::equals(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return false;

   Map<K,V>::RNode n = type_cast<typename Map<K,V>::Node>(o);
   RObject k1 = getKey();
   RObject k2 = n->getKey();
   if(k1 == k2 || (k1 != nullref && k1->equals(k2)))
   {
      RObject v1 = getValue();
      RObject v2 = n->getValue();
      if(v1 == v2 || (v1 != nullref && v1->equals(v2)))
         return true;
   }

   return false;
}


template <class K, class V>
vint WeakHashMap<K,V>::Node::hashCode()
{
   RObject k = getKey();
   RObject v = getValue();

   return ((k==nullref ? 0 : k->hashCode()) ^
            (v==nullref ? 0 : v->hashCode()));
}


template <class K, class V>
RString WeakHashMap<K,V>::Node::toString()
{
   return getKey() + "=" + getValue();
}


template <class K, class V> template <class T>
WeakHashMap<K,V>::HashIterator<T>::HashIterator(RWeakHashMap<K,V> m)
   :map(m)
{
   expectedModCount = map->modCount;
   index = (map->size() != 0 ? map->table->length : 0);
}


template <class K, class V> template <class T>
vbool WeakHashMap<K,V>::HashIterator<T>::hasNext()
{
   RArray<Node> t = map->table;

   while(nextKey == nullref)
   {
      RNode n = node;
      vint i = index;

      while(n == nullref && i > 0)
         n = t[--i];

      node = n;
      index = i;

      if(n == nullref)
      {
         currentKey = nullref;
         return false;
      }

      nextKey = n->get(); // hold on to key in strong ref

      if(nextKey == nullref)
         node = node->next;
   }

   return true;
}


template <class K, class V> template <class T>
typename WeakHashMap<K,V>::RNode WeakHashMap<K,V>::HashIterator<T>::nextNode()
{
   if(map->modCount != expectedModCount)
      ex_throw new StateException("Concurrent Modification");

   if(nextKey == nullref && !hasNext())
      ex_throw new StateException("No such element");

   lastReturned = node;
   node = node->next;
   currentKey = nextKey;
   nextKey = nullref;

   return lastReturned;
}


template <class K, class V> template <class T>
void WeakHashMap<K,V>::HashIterator<T>::remove()
{
   if(lastReturned == nullref)
      ex_throw new StateException("No element to remove");
   
   if(map->modCount != expectedModCount)
      ex_throw new StateException("Concurrent Modification");
   
   map->remove(currentKey);
   expectedModCount = map->modCount;
   lastReturned = nullref;
   currentKey = nullref;
}

template <class K, class V>
WeakHashMap<K,V>::ValueIterator::ValueIterator(RWeakHashMap<K,V> m)
   :HashIterator<V>(m)
{

}

template <class K, class V>
Ref<V> WeakHashMap<K,V>::ValueIterator::next()
{
   return nextNode()->value;
}

template <class K, class V>
WeakHashMap<K,V>::KeyIterator::KeyIterator(RWeakHashMap<K,V> m)
   :HashIterator<K>(m)
{

}

template <class K, class V>
Ref<K> WeakHashMap<K,V>::KeyIterator::next()
{
   return nextNode()->getKey();
}

template <class K, class V>
WeakHashMap<K,V>::NodeIterator::NodeIterator(RWeakHashMap<K,V> m)
   :HashIterator<Map<K,V>::Node>(m)
{

}

template <class K, class V>
typename Map<K,V>::RNode WeakHashMap<K,V>::NodeIterator::next()
{
   return nextNode();
}

template <class K, class V>
RIterator<K> WeakHashMap<K,V>::newKeyIterator()
{
   return new KeyIterator(thisref);
}

template <class K, class V>
RIterator<V> WeakHashMap<K,V>::newValueIterator()
{
   return new ValueIterator(thisref);
}

template <class K, class V>
RIterator<typename Map<K,V>::Node> WeakHashMap<K,V>::newNodeIterator()
{
   return new NodeIterator(thisref);
}

template <class K, class V>
RSet<K> WeakHashMap<K,V>::keySet()
{
   RSet<K> ks = theKeySet;

   return (ks != nullref ? ks : (theKeySet = new KeySet(thisref)));
}

template <class K, class V>
WeakHashMap<K,V>::KeySet::KeySet(RWeakHashMap<K,V> m)
   :map(m)
{

}

template <class K, class V>
RIterator<K> WeakHashMap<K,V>::KeySet::iterator()
{
   return map->newKeyIterator();
}

template <class K, class V>
vint WeakHashMap<K,V>::KeySet::size()
{
   return map->size();
}

template <class K, class V>
vbool WeakHashMap<K,V>::KeySet::contains(RObject o)
{
   return map->containsKey(o);
}

template <class K, class V>
vbool WeakHashMap<K,V>::KeySet::remove(RObject o)
{
   if(map->containsKey(o))
   {
      map->remove(o);
      return true;
   }

   return false;
}

template <class K, class V>
void WeakHashMap<K,V>::KeySet::clear()
{
   map->clear();
}

template <class K, class V>
RCollection<V> WeakHashMap<K,V>::values()
{
   RCollection<V> vs = theValues;

   return (vs != nullref ? vs : (theValues = new Values(thisref)));
}

template <class K, class V>
WeakHashMap<K,V>::Values::Values(RWeakHashMap<K,V> m)
   :map(m)
{

}

template <class K, class V>
RIterator<V> WeakHashMap<K,V>::Values::iterator()
{
   return map->newValueIterator();
}

template <class K, class V>
vint WeakHashMap<K,V>::Values::size()
{
   return map->size();
}

template <class K, class V>
vbool WeakHashMap<K,V>::Values::contains(RObject o)
{
   return map->containsValue(o);
}

template <class K, class V>
void WeakHashMap<K,V>::Values::clear()
{
   map->clear();
}

template <class K, class V>
RSet<typename Map<K,V>::Node> WeakHashMap<K,V>::nodeSet()
{
   RSet<typename Map<K,V>::Node> ns = theNodeSet;
   
   return (ns != nullref ? ns : (theNodeSet = new NodeSet(thisref)));
}

template <class K, class V>
WeakHashMap<K,V>::NodeSet::NodeSet(RWeakHashMap<K,V> m)
   :map(m)
{

}

template <class K, class V>
RIterator<typename Map<K,V>::Node> WeakHashMap<K,V>::NodeSet::iterator()
{
   return map->newNodeIterator();
}

template <class K, class V>
vbool WeakHashMap<K,V>::NodeSet::contains(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return false;

   Map<K,V>::RNode n = type_cast<typename Map<K,V>::Node>(o);
   RNode candidate = map->getNode(n->getKey());

   return candidate != nullref && candidate->equals(n);
}

template <class K, class V>
vbool WeakHashMap<K,V>::NodeSet::remove(RObject o)
{
   return map->removeMapping(o) != nullref;
}

template <class K, class V>
vint WeakHashMap<K,V>::NodeSet::size()
{
   return map->size();
}

template <class K, class V>
void WeakHashMap<K,V>::NodeSet::clear()
{
   map->clear();
}

template <class K, class V>
RArray<typename Map<K,V>::Node> WeakHashMap<K,V>::NodeSet::toArray()
{
   RArray<Map<K,V>::Node> ar = new Array<Map<K,V>::Node>(map->size());

   int i = 0;
   
   RIterator<Map<K,V>::Node> it = map->nodeSet()->iterator();
   
   while(it->hasNext())
      ar[i++] = new AbstractMap<K, V>::SimpleNode(it->next());
   
   return ar;
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_WEAKHASHMAP_H */
