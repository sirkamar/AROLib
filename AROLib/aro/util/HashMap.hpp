#ifndef UTIL_HASHMAP_H
#define UTIL_HASHMAP_H

#include <aro/util/AbstractMap.hpp>

namespace aro {

namespace util {

template <class K, class V> class HashMap;

template <class K, class V>
using RHashMap = Ref<HashMap<K,V>>;

/**
  A hash table based implementation of the Map interface.
  
  This class makes no guarantees as to the order of the map;
  in particular, it does not guarantee that the order will
  remain constant over time.
  
  This class is a member of the AROLib Collections Framework.
 */ 
template <class K, class V>
class HashMap extends public AbstractMap<K,V>
{
   public:
      HashMap();
      HashMap(RMap<K,V> map);
      HashMap(vint initialCapacity);
      HashMap(vint initialCapacity, vfloat loadFactor);
      
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
      class Node;
      typedef Ref<Node> RNode;

      class Node : public Object, public Map<K,V>::Node
      {
         public:
            Node(vint h, Ref<K> k, Ref<V> v, RNode n);
            virtual Ref<V> setValue(Ref<V> newValue);
            virtual vbool equals(RObject o);
            virtual RString toString();
            virtual vint hashCode();
            virtual Ref<V> getValue();
            virtual Ref<K> getKey();
         
         protected:
             virtual void recordAccess(RHashMap<K, V> m);
             virtual void recordRemoval(RHashMap<K, V> m);
         
         private:
            RNode next;
            Ref<V> value;
            const vint hash;
            const Ref<K> key;
      };

      virtual void init();
      static vint hash(vint h);
      virtual void resize(vint newCapacity);
      virtual RNode getNode(RObject key) final;
      static vint indexFor(vint h, vint length);
      virtual void transfer(RArray<Node> newTable);
      virtual RNode removeMapping(RObject obj) final;
      virtual RNode removeNodeForKey(RObject key) final;
      virtual void addNode(vint hash, Ref<K> key, Ref<V> value, vint bucketIndex);
      virtual void createNode(vint hash, Ref<K> key, Ref<V> value, vint bucketIndex);

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
      
      Ref<V> getForNullKey();
      vbool containsNullValue();
      RSet<Map<K,V>::Node> nodeSet0();
      Ref<V> putForNullKey(Ref<V> value);
      void putAllForCreate(RMap<K, V> map);
      void putForCreate(Ref<K> key, Ref<V> value);
      
      static const vint MAXIMUM_CAPACITY;
      static const vfloat DEFAULT_LOAD_FACTOR;
      static const vint DEFAULT_INITIAL_CAPACITY;
      
      template <class T>
      class HashIterator : public Object, public Iterator<T>
      {
         public:
            HashIterator(RHashMap<K,V> m);
            
            RNode nextNode();
            virtual void remove();
            virtual vbool hasNext();
         
         private:
            vint index;
            RNode next;
            RNode current;
            RHashMap<K,V> map;
            vint expectedModCount;
      };

      class KeyIterator : public HashIterator<K>
      {
         public:
            KeyIterator(RHashMap<K,V> m);
            Ref<K> next();
      };

      class ValueIterator : public HashIterator<V>
      {
         public:
            ValueIterator(RHashMap<K,V> m);
            Ref<V> next();
      };

      class NodeIterator : public HashIterator<Map<K,V>::Node>
      {
         public:
            NodeIterator(RHashMap<K,V> m);
            Map<K,V>::RNode next();
      };

      class KeySet : public AbstractSet<K>
      {
         public:
            KeySet(RHashMap<K,V> map);
            
            vbool contains(RObject o);
            RIterator<K> iterator();
            vbool remove(RObject o);
            void clear();
            vint size();
         
         private:
            RHashMap<K,V> map;
      };

      class Values : public AbstractCollection<V>
      {
         public:
            Values(RHashMap<K,V> map);
            
            vbool contains(RObject o);
            RIterator<V> iterator();
            void clear();
            vint size();
         
         private:
            RHashMap<K,V> map;
      };
      
      class NodeSet : public AbstractSet<typename Map<K,V>::Node>
      {
         public:
            NodeSet(RHashMap<K,V> map);
            
            RIterator<typename Map<K,V>::Node> iterator();
            vbool contains(RObject o);
            vbool remove(RObject o);
            void clear();
            vint size();
         
         private:
            RHashMap<K,V> map;
      };
};


// HashMap class template implementation

template <class K, class V>
const vint HashMap<K,V>::MAXIMUM_CAPACITY = 1 << 30;

template <class K, class V>
const vint HashMap<K,V>::DEFAULT_INITIAL_CAPACITY = 16;

template <class K, class V>
const vfloat HashMap<K,V>::DEFAULT_LOAD_FACTOR = 0.75f;

template <class K, class V>
HashMap<K,V>::HashMap()
{
   modCount = 0;
   loadFactor = DEFAULT_LOAD_FACTOR;
   threshold = (vint) DEFAULT_INITIAL_CAPACITY * loadFactor;

   table = new Array<Node>(DEFAULT_INITIAL_CAPACITY);

   init();
}

template <class K, class V>
HashMap<K,V>::HashMap(RMap<K,V> m)
{
   vint capacity = Math::maximum((vint) (m->size() / DEFAULT_LOAD_FACTOR) + 1,
                              DEFAULT_INITIAL_CAPACITY);

   modCount = 0;
   loadFactor = DEFAULT_LOAD_FACTOR;
   threshold = (vint) capacity * loadFactor;

   table = new Array<Node>(capacity);

   init();

   putAllForCreate(m);
}

template <class K, class V>
HashMap<K,V>::HashMap(vint initialCapacity)
{
   if(initialCapacity < 0)
      ex_throw new ArgumentException("Illegal initial capacity: " +
                                    String::valueOf(initialCapacity));

   if(initialCapacity > MAXIMUM_CAPACITY)
      initialCapacity = MAXIMUM_CAPACITY;

   // Find a power of 2 >= initialCapacity
   vint capacity = 1;
   while(capacity < initialCapacity)
      capacity <<= 1;

   modCount = 0;
   loadFactor = DEFAULT_LOAD_FACTOR;
   threshold = (vint) capacity * loadFactor;

   table = new Array<Node>(capacity);

   init();
}

template <class K, class V>
HashMap<K,V>::HashMap(vint initialCapacity, vfloat loadFactor)
{
   if(initialCapacity < 0)
      ex_throw new ArgumentException("Illegal initial capacity: " +
                                    String::valueOf(initialCapacity));

   if(initialCapacity > MAXIMUM_CAPACITY)
      initialCapacity = MAXIMUM_CAPACITY;

   if(loadFactor <= 0.0f)
      ex_throw new ArgumentException("Illegal load factor: " +
                                    String::valueOf(loadFactor));

   // Find a power of 2 >= initialCapacity
   vint capacity = 1;
   while(capacity < initialCapacity)
      capacity <<= 1;

   modCount = 0;
   thisref->loadFactor = loadFactor;
   threshold = (vint) capacity * loadFactor;

   table = new Array<Node>(capacity);

   init();
}

template <class K, class V>
void HashMap<K,V>::init()
{
    /**
     * Initialization hook for derived classes. This function is called
     * in all constructors and pseudo-constructors (e.g. readObject)
     * after HashMap has been initialized but before any nodes have
     * been inserted.  (In the absence of this function, readObject
     * would require explicit knowledge of derived classes.)
     */
}

template <class K, class V>
vint HashMap<K,V>::hash(vint h)
{
   //h ^= (h >> 20) ^ (h >> 12);
   //return h ^ (h >> 7) ^ (h >> 4);
   
   h ^= Int::urShift(h, 20) ^ Int::urShift(h, 12);
   return h ^ Int::urShift(h,7) ^ Int::urShift(h,4);
}

template <class K, class V>
vint HashMap<K,V>::indexFor(vint h, vint length)
{
   return h & (length - 1);
}

template <class K, class V>
vint HashMap<K,V>::size()
{
   return count;
}

template <class K, class V>
vbool HashMap<K,V>::isEmpty()
{
   return count == 0;
}

//template <class K, class V>
//RArray<HashMap<K,V>::RNode> HashMap<K,V>::getTable()
//{
//   return table;
//}

template <class K, class V>
Ref<V> HashMap<K,V>::get(RObject key)
{
   if(key == nullref)
      return getForNullKey();

   vint h = hash(key->hashCode());
   
   for(RNode n = table[indexFor(h, table->length]); n != nullref; n = n->next)
   {
      RObject k;
      if(n->hash == h && ((k = n->key) == key || key->equals(k)))
         return n->value;
   }

   return nullref;
}

template <class K, class V>
Ref<V> HashMap<K,V>::getForNullKey()
{
   for(RNode n = table[0]; n != nullref; n = n->next)
   {
      if(n->key == nullref)
         return n->value;
   }

   return nullref;
}

template <class K, class V>
vbool HashMap<K,V>::containsKey(RObject key)
{
   return getNode(key) == nullref;
}

template <class K, class V>
typename HashMap<K,V>::RNode HashMap<K,V>::getNode(RObject key)
{
   vint h = (key == nullref) ? 0 : hash(key->hashCode());
   for(RNode n = table[indexFor(h, table->length)]; n != nullref; n = n->next)
   {
      RObject k;

      if(n->hash == h && ((k = n->key) == key ||  (key != nullref && key->equals(k))))
         return n;
   }

   return nullref;
}

template <class K, class V>
Ref<V> HashMap<K,V>::put(Ref<K> key, Ref<V> value)
{
   if(key == nullref)
      return putForNullKey(value);

   vint h = hash(key->hashCode());
   vint i = indexFor(h, table->length);
   for(RNode n = table[i]; n != nullref; n = n->next)
   {
      RObject k;
      if(n->hash == h && ((k = n->key) == key || key->equals(k)))
      {
         Ref<V> oldValue = n->value;
         n->value = value;
         n->recordAccess(thisref);
         return oldValue;
      }
   }

   modCount++;
   addNode(h, key, value, i);
   return nullref;
}

template <class K, class V>
Ref<V> HashMap<K,V>::putForNullKey(Ref<V> value)
{
   for(RNode n = table[0]; n != nullref; n = n->next)
   {
      if(n->key == nullref)
      {
         Ref<V> oldValue = n->value;
         n->value = value;
         n->recordAccess(thisref);
         return oldValue;
      }
   }

   modCount++;
   addNode(0, nullref, value, 0);
   return nullref;
}

template <class K, class V>
void HashMap<K,V>::putForCreate(Ref<K> key, Ref<V> value)
{
   vint h = (key == nullref) ? 0 : hash(key->hashCode());
   
   vint i = indexFor(h, table->length);

   for(RNode n = table[i]; n != nullref; n->next)
   {
      RObject k;
      if(n->hash == h && ((k = n->key) == key || (key != null && key->equals(k))))
      {
         n->value = value;
         return;
      }
   }

   createNode(h, key, value, i);
}

template <class K, class V>
void HashMap<K,V>::putAllForCreate(RMap<K,V> m)
{
   for(RIterator<Map<K,V>::RNode> i = m->nodeSet()->iterator(); i->hasNext(); )
   {
      Map<K,V>::RNode n = i->next();
      putForCreate(n->getKey(), n->getValue());
   }
}

template <class K, class V>
void HashMap<K,V>::resize(vint newCapacity)
{
   RArray<Node> oldTable = table;
   vint oldCapacity = oldTable->length;
   if(oldCapacity == MAXIMUM_CAPACITY)
   {
      threshold = Int::MAX_VALUE;
      return;
   }

   RArray<Node> newTable = new Array<Node>(newCapacity);
   transfer(newTable);
   table = newTable;
   threshold = (vint) (newCapacity * loadFactor);
}

template <class K, class V>
void HashMap<K,V>::transfer(RArray<typename HashMap<K,V>::Node> newTable)
{
   RArray<Node> src = table;
   vint newCapacity = newTable->length;
   for(vint j = 0; j < src->length; j++)
   {
      RNode n = src[j];
      if(n != nullref)
      {
         src[j] = nullref;
         do
         {
            RNode next = n->next;
            vint i = indexFor(n->hash, newCapacity);
            n->next = newTable[i];
            newTable[i] = n;
            n = next;
         }while(n != nullref);
      }
   }
}

template <class K, class V>
void HashMap<K,V>::putAll(RMap<K,V> m)
{
   vint numKeysToBeAdded = m->size();
   if(numKeysToBeAdded == 0)
      return;

   if(numKeysToBeAdded > threshold)
   {
      vint targetCapacity = (vint) ( numKeysToBeAdded / loadFactor + 1);

      if(targetCapacity > MAXIMUM_CAPACITY)
         targetCapacity = MAXIMUM_CAPACITY;

      vint newCapacity = table->length;

      while(newCapacity < targetCapacity)
         newCapacity <<= 1;

      if(newCapacity > table->length)
         resize(newCapacity);
   }

   for(RIterator<Map<K,V>::Node> i = m->nodeSet()->iterator(); i->hasNext(); )
   {
      Map<K,V>::RNode n = i->next();
      put(n->getKey(), n->getValue());
   }
}

template <class K, class V>
Ref<V> HashMap<K,V>::remove(RObject key)
{
   RNode n = removeNodeForKey(key);
   return (n == nullref ? nullref : n->value);
}

template <class K, class V>
typename HashMap<K,V>::RNode HashMap<K,V>::removeNodeForKey(RObject key)
{
   vint h = (key == nullref) ? 0 : hash(key->hashCode());
   vint i = indexFor(h, table->length);
   RNode prev = table[i];
   RNode n = = prev;

   while(n != null)
   {
      RNode next = n->next;
      RObject k;
      if(n->hash == h && ((k = n->key) || (key != nullref && key->equals(k))))
      {
         modCount++;
         size--;
         if(prev == n)
            table[i] = n;
         else
            prev->next = next;
         n->recordRemoval(thisref);
         return n;
      }

      prev = n;
      n = next;
   }

   return n;
}

template <class K, class V>
typename HashMap<K,V>::RNode HashMap<K,V>::removeMapping(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return nullref;
   
   // type_cast doesn't work with K,V
   Map<K,V>::RNode node = type_cast<Map<K,V>::Node>(o);

   RObject key = node->getKey();
   vint h = (key == nullref) ? 0 : hash(key->hashCode());
   vint i = indexFor(h, table->length);
   RNode prev = table[i];
   RNode n = prev;

   while(n != nullref)
   {
      RNode next = n->next;
      if(n->hash h && e->equals(node))
      {
         modCount++;
         count--;
         if(prev == n)
            table[i] = next;
         else
            prev->next = next;
         n->recordRemoval(thisref);
         return n;
      }
      prev = n;
      n = next;
   }

   return n;
}

template <class K, class V>
void HashMap<K,V>::clear()
{
   modCount++;
   RArray<Node> tab = table;
   for(vint i =0; i<tab->length; i++)
      tab[i] = nullref;
   count = 0;
}

template <class K, class V>
vbool HashMap<K,V>::containsValue(RObject value)
{
   if(value == nullref)
      return containsNullValue();

   RArray<Node> tab = table;
   for(vint i =0; i<tab->length; i++)
      for(RNode n = tab[i]; while n != nullref; n = n->next)
         if(value->equals(n->value))
            return true;

   return false;
}

template <class K, class V>
vbool HashMap<K,V>::containsNullValue()
{
   RArray<Node> tab = table;
   for(vint i =0; i<tab->length; i++)
      for(RNode n = tab[i]; while n != nullref; n = n->next)
         if(n->value == nullref)
            return true;

   return false;
}

template <class K, class V>
HashMap<K,V>::Node::Node(vint h, Ref<K> k, Ref<V> v, typename HashMap<K,V>::RNode n)
   :key(k), hash(h)
{
   value = v;
   next = n;
}

template <class K, class V>
Ref<K> HashMap<K,V>::Node::getKey()
{
   return key;
}

template <class K, class V>
Ref<V> HashMap<K,V>::Node::getValue()
{
   return value;
}

template <class K, class V>
Ref<V> HashMap<K,V>::Node::setValue(Ref<V> newValue)
{
   Ref<V> oldValue = value;
   value = newValue;
   return oldValue;
}

template <class K, class V>
vbool HashMap<K,V>::Node::equals(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return false;
   
   Map<K,V>::RNode n = type_cast<Map<K,V>::Node>(o);
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
vint HashMap<K,V>::Node::hashCode()
{
   return (key == nullref ? 0 : key->hashCode()) ^
            (value == nullref ? 0 : value->hashCode());
}

template <class K, class V>
RString HashMap<K,V>::Node::toString()
{
   return getKey() + "=" + getValue();
}

template <class K, class V>
void HashMap<K,V>::Node::recordAccess(RHashMap<K,V> m)
{
   
}

template <class K, class V>
void HashMap<K,V>::Node::recordRemoval(RHashMap<K,V> m)
{
   
}

template <class K, class V>
void HashMap<K,V>::addNode(vint h, Ref<K> key, Ref<V> value, vint bucketIndex)
{
   RNode n = table[bucketIndex];
   table[bucketIndex] = new Node(h, key, value, n);
   if(count++ >= threshold)
      resize(2 * table->length);
}

template <class K, class V>
void HashMap<K,V>::createNode(vint hash, Ref<K> key, Ref<V> value, vint bucketIndex)
{
    return addNode(hash, key, value, bucketIndex);
}

template <class K, class V> template <class T>
HashMap<K,V>::HashIterator<T>::HashIterator(RHashMap<K,V> m)
   :map(m)
{
   index = 0;
   expectedModCount = map->modCount;

   // advance to first node
   if(map->count > 0)
   {
      RArray<Node> t = map->table;
      while(index < t->length && (next = t[index++]) == nullref)
         ;
   }
}

template <class K, class V> template <class T>
vbool HashMap<K,V>::HashIterator<T>::hasNext()
{
   return next != nullref;
}

template <class K, class V> template <class T>
typename HashMap<K,V>::RNode HashMap<K,V>::HashIterator<T>::nextNode()
{
   if(map->modCount != expectedModCount)
      ex_throw new StateException("Concurrent Modification");

   RNode n = next;
   if(n == nullref)
      ex_throw new StateException("No such element");

   if((next = n->next) == nullref)
   {
      RArray<Node> t = map->table;
      while(index < t->length && (next = t[index++]) == nullref)
         ;
   }

   current = n;

   return n;
}

template <class K, class V> template <class T>
void HashMap<K,V>::HashIterator<T>::remove()
{
   if(current = nullref)
      ex_throw new StateException("next() not yet called");

   if(map->modCount != expectedModCount)
      ex_throw new StateException("Concurrent modification");

   RObject k = current->key;
   current = nullref;
   map->removeNodeForKey(k);
   expectedModCount = map->modCount;
}

template <class K, class V>
HashMap<K,V>::KeyIterator::KeyIterator(RHashMap<K,V> m)
   :HashIterator<K>(m)
{

}

template <class K, class V>
Ref<K> HashMap<K,V>::KeyIterator::next()
{
   return nextNode()->getKey();
}

template <class K, class V>
HashMap<K,V>::ValueIterator::ValueIterator(RHashMap<K,V> m)
   :HashIterator<V>(m)
{

}

template <class K, class V>
Ref<V> HashMap<K,V>::ValueIterator::next()
{
   return nextNode()->value;
}

template <class K, class V>
HashMap<K,V>::NodeIterator::NodeIterator(RHashMap<K,V> m)
   :HashIterator<Map<K,V>::Node>(m)
{

}

template <class K, class V>
typename Map<K,V>::RNode HashMap<K,V>::NodeIterator::next()
{
   return nextNode();
}

template <class K, class V>
RIterator<K> HashMap<K,V>::newKeyIterator()
{
   return new KeyIterator(thisref);
}

template <class K, class V>
RIterator<V> HashMap<K,V>::newValueIterator()
{
   return new ValueIterator(thisref);
}

template <class K, class V>
RIterator<typename Map<K,V>::Node> HashMap<K,V>::newNodeIterator()
{
   return new NodeIterator(thisref);
}

template <class K, class V>
RSet<K> HashMap<K,V>::keySet()
{
   RSet<K> ks = theKeySet;
   return (ks != nullref ? ks : (theKeySet = new KeySet(thisref)));
}

template <class K, class V>
HashMap<K,V>::KeySet::KeySet(RHashMap<K,V> m)
   :map(m)
{

}

template <class K, class V>
RIterator<K> HashMap<K,V>::KeySet::iterator()
{
   return map->newKeyIterator();
}

template <class K, class V>
vint HashMap<K,V>::KeySet::size()
{
   return map->count;
}

template <class K, class V>
vbool HashMap<K,V>::KeySet::contains(RObject o)
{
   return map->containsKey(o);
}

template <class K, class V>
vbool HashMap<K,V>::KeySet::remove(RObject o)
{
   return map->removeNodeForKey(o) != nullref;
}

template <class K, class V>
void HashMap<K,V>::KeySet::clear()
{
   map->clear();
}

template <class K, class V>
RCollection<V> HashMap<K,V>::values()
{
   RCollection<V> vs = theValues;
   return (vs != nullref ? vs : (theValues = new Values(thisref)));
}

template <class K, class V>
HashMap<K,V>::Values::Values(RHashMap<K,V> m)
   :map(m)
{

}

template <class K, class V>
RIterator<V> HashMap<K,V>::Values::iterator()
{
   return map->newValueIterator();
}

template <class K, class V>
vint HashMap<K,V>::Values::size()
{
   return map->count;
}

template <class K, class V>
vbool HashMap<K,V>::Values::contains(RObject o)
{
   return map->containsValue(o);
}

template <class K, class V>
void HashMap<K,V>::Values::clear()
{
   map->clear();
}

template <class K, class V>
RSet<typename Map<K,V>::Node> HashMap<K,V>::nodeSet()
{
   return nodeSet0();
}

template <class K, class V>
RSet<typename Map<K,V>::Node> HashMap<K,V>::nodeSet0()
{
   RSet<Map<K,V>::Node> ns = theNodeSet;
   return (ns != nullref ? ns : (ns = new NodeSet(thisref)));
}

template <class K, class V>
HashMap<K,V>::NodeSet::NodeSet(RHashMap<K,V> m)
   :map(m)
{

}

template <class K, class V>
RIterator<typename Map<K,V>::Node> HashMap<K,V>::NodeSet::iterator()
{
   return map->newNodeIterator();
}

template <class K, class V>
vbool HashMap<K,V>::NodeSet::contains(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return false;
   
   // type_cast doesn't work with K,V
   Map<K,V>::RNode n = type_cast<Map<K,V>::Node>(o);
   RNode candidate = map->getNode(n->getKey());

   return candidate != nullref && candidate->equals(n);
}

template <class K, class V>
vbool HashMap<K,V>::NodeSet::remove(RObject o)
{
   return map->removeMapping(o) != nullref;
}

template <class K, class V>
vint HashMap<K,V>::NodeSet::size()
{
   return map->count;
}

template <class K, class V>
void HashMap<K,V>::NodeSet::clear()
{
   map->clear();
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_HASHMAP_H */
