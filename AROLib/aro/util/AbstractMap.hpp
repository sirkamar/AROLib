#ifndef UTIL_ABSTRACTMAP_H
#define UTIL_ABSTRACTMAP_H

#include <aro/util/Map.hpp>
#include <aro/util/AbstractSet.hpp>

namespace aro {

namespace util {

template <class K, class V> class AbstractMap;

template <class K, class V>
using RAbstractMap = Ref<AbstractMap<K,V>>;

/**
 * AbstractMap class template declaration
 */ 
template <class K, class V>
class AbstractMap : public Object, public Map<K,V>
{
   public:
      virtual vint size();
      virtual void clear();
      virtual vbool isEmpty();
      virtual RSet<K> keySet();
      virtual Ref<V> get(RObject key);
      virtual Ref<V> put(Ref<K> key, Ref<V> val);
      virtual Ref<V> remove(RObject key);
      virtual RCollection<V> values();
      virtual void putAll(RMap<K,V> map);
      virtual vbool containsKey(RObject key);
      virtual vbool containsValue(RObject val);

      virtual vint hashCode();
      virtual RString toString();
      virtual vbool equals(RObject obj);

      virtual RSet<Map<K,V>::Node> nodeSet()=0;

      class SimpleNode : public Object, public Map<K,V>::Node
      {
         public:
            SimpleNode(Ref<K> key, Ref<V> value);
            SimpleNode(Map<K,V>::RNode node);

            virtual Ref<K> getKey();
            virtual Ref<V> getValue();
            virtual Ref<V> setValue(Ref<V> value);

            virtual vint hashCode();
            virtual RString toString();
            virtual vbool equals(RObject obj);

         private:
            const Ref<K> key;
            Ref<V> value;
      };

      class SimpleImmutableNode : public Object, public Map<K,V>::Node
      {
            SimpleImmutableNode(Ref<K> key, Ref<V> value);
            SimpleImmutableNode(Map<K,V>::RNode node);

            virtual Ref<K> getKey();
            virtual Ref<V> getValue();
            virtual Ref<V> setValue(Ref<V> value);

            virtual vint hashCode();
            virtual RString toString();
            virtual vbool equals(RObject obj);

         private:
            const Ref<K> key;
            const Ref<V> value;
      };

      typedef Ref<SimpleNode> RSimpleNode;
      typedef Ref<SimpleImmutableNode> RSimpleImmutableNode;

   protected:
      AbstractMap();
      
      RSet<K> theKeySet;
      RCollection<V> theValues;
   
   private:
      static vbool eq(RObject o1, RObject o2);
};


// AbstractMap class template Implementation

template <class K, class V>
AbstractMap<K,V>::AbstractMap()
{
   theKeySet = nullref;
   theValues = nullref;
}

template <class K, class V>
vint AbstractMap<K,V>::size()
{
   return nodeSet()->size();
}

template <class K, class V>
vbool AbstractMap<K,V>::isEmpty()
{
   return size() == 0;
}

template <class K, class V>
vbool AbstractMap<K,V>::containsValue(RObject value)
{
   RIterator<Node> i = nodeSet()->iterator();

   if(value == nullref)
   {
      while(i->hasNext())
      {
         RNode n = i->next();

         if(n->getValue() == nullref)
            return true;
      }
   }
   else
   {
      while(i->hasNext())
      {
         RNode n = i->next();

         if(value->equals(n->getValue()))
            return true;
      }
   }

   return false;
}

template <class K, class V>
vbool AbstractMap<K,V>::containsKey(RObject key)
{
   RIterator<Node> i = nodeSet()->iterator();

   if(key == nullref)
   {
      while(i->hasNext())
      {
         RNode n = i->next();

         if(n->getKey() == nullref)
            return true;
      }
   }
   else
   {
      while(i->hasNext())
      {
         RNode n = i->next();

         if(key->equals(n->getKey()))
            return true;
      }
   }

   return false;
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::get(RObject key)
{
   RIterator<Node> i = nodeSet()->iterator();

   if(key == nullref)
   {
      while(i->hasNext())
      {
         RNode n = i->next();

         if(n->getKey() == nullref)
            return n->getValue();
      }
   }
   else
   {
      while(i->hasNext())
      {
         RNode n = i->next();

         if(key->equals(n->getKey()))
            return n->getValue();
      }
   }
   
   return nullref;
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::put(Ref<K> key, Ref<V> value)
{
   ex_throw new UnsupportedException("put() not supported");
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::remove(RObject key)
{
   RIterator<Node> i = nodeSet()->iterator();
   RNode correctNode = nullref;

   if(key == nullref)
   {
      while(correctNode == nullref && i->hasNext())
      {
         RNode n = i->next();

         if(n->getKey() == nullref)
            correctNode = n;
      }
   }
   else
   {
      while(correctNode == nullref && i->hasNext())
      {
         RNode n = i->next();

         if(key->equals(n->getKey()))
            correctNode = n;
      }
   }
   
   Ref<V> oldValue = nullref;
   if(correctNode != nullref)
   {
      oldValue = correctNode->getValue();
      i->remove();
   }

   return oldValue;
}

template <class K, class V>
void AbstractMap<K,V>::putAll(RMap<K,V> map)
{
   RIterator<Node> it = map->nodeSet()->iterator();

   while(it->hasNext())
   {
      RNode n = it->next();
      
      put(n->getKey(), n->getValue());
   }
}

template <class K, class V>
void AbstractMap<K,V>::clear()
{
   nodeSet()->clear();
}

template <class K, class V>
class AbstractMapKeySet : public AbstractSet<K>
{
   public:
      AbstractMapKeySet(RAbstractMap<K,V> map)
      {
         thisref->map = map;
      }

      RIterator<K> iterator()
      {
         return new AbstractMapKeySetItr(map->nodeSet()->iterator());
      }

      vbool contains(RObject k)
      {
         return map->containsKey(k);
      }

      vint size()
      {
         return map->size();
      }

   private:
      RAbstractMap<K,V> map;

      class AbstractMapKeySetItr : public Object, public Iterator<K>
      {
         public:
            AbstractMapKeySetItr(RIterator<typename Map<K,V>::Node> i)
            {
               thisref->i = i;
            }

            vbool hasNext()
            {
               return i->hasNext();
            }

            void remove()
            {
               i->remove();
            }

            Ref<K> next()
            {
               return i->next()->getKey();
            }

         private:
            RIterator<typename Map<K,V>::Node> i;
      };
};

template <class K, class V>
RSet<K> AbstractMap<K,V>::keySet()
{
   if(theKeySet == nullref)
      theKeySet = new AbstractMapKeySet<K,V>(thisref);

   return theKeySet;
}

template <class K, class V>
class AbstractMapValues : public AbstractCollection<V>
{
   public:
      AbstractMapValues(RAbstractMap<K,V> map)
      {
         thisref->map = map;
      }

      RIterator<V> iterator()
      {
         return new AbstractMapValuesItr(map->nodeSet()->iterator());
      }

      vbool contains(RObject v)
      {
         return map->containsValue(v);
      }

      vint size()
      {
         return map->size();
      }

   private:
      RAbstractMap<K,V> map;

      class AbstractMapValuesItr : public Object, public Iterator<V>
      {
         public:
            AbstractMapValuesItr(RIterator<typename Map<K,V>::Node> i)
            {
               thisref->i = i;
            }

            vbool hasNext()
            {
               return i->hasNext();
            }

            void remove()
            {
               i->remove();
            }

            Ref<V> next()
            {
               return i->next()->getValue();
            }

         private:
            RIterator<typename Map<K,V>::Node> i;
      };
};

template <class K, class V>
RCollection<V> AbstractMap<K,V>::values()
{
   if(theValues == nullref)
      theValues = new AbstractMapValues<K,V>(thisref);

   return theValues;
}

template <class K, class V>
vbool AbstractMap<K,V>::equals(RObject o)
{
   if(o == thisref)
      return true;

   // type_of doesn't work with K,V
   if(!type_of<Map<K,V>>(o))
      return false;
   
   // type_cast doesn't work with K,V
   RMap<K,V> m = type_cast<Map<K,V>>(o);

   if(m->size() != size())
      return false;

   ex_try
   {
      RIterator<Node> i = nodeSet()->iterator();

      while(i->hasNext())
      {
         RNode n = i->next();
         Ref<K> key = n->getKey();
         Ref<V> value = n->getValue();

         if(value == nullref)
         {
            if(!(m->get(key)==nullref && m->containsKey(key)))
               return false;
         }
         else
         {
            if(!value->equals(m->get(key)))
               return false;
         }
      }
   }
   ex_catch
   {
      ex_handle(NullException)
      {
         return false;
      }
   }
   ex_end

   return true;
}

template <class K, class V>
vint AbstractMap<K,V>::hashCode()
{
   vint h = 0;
   RIterator<Node> i = nodeSet()->iterator();

   while(i->hasNext())
      h += i->next()->hashCode();

   return h;
}

template <class K, class V>
RString AbstractMap<K,V>::toString()
{
   RIterator<Node> i = nodeSet()->iterator();
   if(!i->hasNext())
      return "{}";

   RStringBuilder sb = new StringBuilder();
   sb->append("{");
   for(;;)
   {
      RNode n = i->next();
      Ref<K> key = n->getKey();
      Ref<V> value = n->getValue();
      RObject thisMap = "(thisref map)";


      sb->append(key == thisref ? thisMap : key);
      sb->append("=");
      sb->append(value == thisref ? thisMap : value);

      if(i->hasNext())
         sb->append(", ");
   }

   return sb->append("}")->toString();
}

template <class K, class V>
vbool AbstractMap<K,V>::eq(RObject o1, RObject o2)
{
   return o1 == nullref ? o2 == nullref : o1->equals(o2);
}

template <class K, class V>
AbstractMap<K,V>::SimpleNode::SimpleNode(Ref<K> key, Ref<V> value)
   :key(key)
{
   value = value;
}

template <class K, class V>
AbstractMap<K,V>::SimpleNode::SimpleNode(typename Map<K,V>::RNode node)
   :key(node->getKey())
{
   value = node->getValue();
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::SimpleNode::setValue(Ref<V> value)
{
   Ref<V> oldValue = thisref->value;
   thisref->value = value;
   return oldValue;
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::SimpleNode::getValue()
{
   return value;
}

template <class K, class V>
Ref<K> AbstractMap<K,V>::SimpleNode::getKey()
{
   return key;
}

template <class K, class V>
vbool AbstractMap<K,V>::SimpleNode::equals(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return false;

   RNode n = type_cast<Map<K,V>::Node>(o);

   return eq(key, n->getKey()) && eq(value, n->getValue());
}

template <class K, class V>
vint AbstractMap<K,V>::SimpleNode::hashCode()
{
   return (key == nullref ? 0 : key->hashCode()) ^
      (value == nullref ? 0 : value->hashCode());
}

template <class K, class V>
RString AbstractMap<K,V>::SimpleNode::toString()
{
   return key + "=" + value;
}

template <class K, class V>
AbstractMap<K,V>::SimpleImmutableNode::SimpleImmutableNode(Ref<K> key, Ref<V> value)
   :key(key), value(value)
{
   
}

template <class K, class V>
AbstractMap<K,V>::SimpleImmutableNode::SimpleImmutableNode(Map<K,V>::RNode node)
   :key(node->getKey()), value(node->getValue())
{
   
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::SimpleImmutableNode::setValue(Ref<V> value)
{
   ex_throw new UnsupportedException("setValue() not supported");
}

template <class K, class V>
Ref<V> AbstractMap<K,V>::SimpleImmutableNode::getValue()
{
   return value;
}

template <class K, class V>
Ref<K> AbstractMap<K,V>::SimpleImmutableNode::getKey()
{
   return key;
}

template <class K, class V>
vbool AbstractMap<K,V>::SimpleImmutableNode::equals(RObject o)
{
   if(!type_of<Map<K,V>::Node>(o))
      return false;
   
   // type_cast doesn't work with K,V
   RNode n = type_cast<Map<K,V>::Node>(o);

   return eq(key, n->getKey()) && eq(value, n->getValue());
}

template <class K, class V>
vint AbstractMap<K,V>::SimpleImmutableNode::hashCode()
{
   return (key == nullref ? 0 : key->hashCode()) ^
      (value == nullref ? 0 : value->hashCode());
}

template <class K, class V>
RString AbstractMap<K,V>::SimpleImmutableNode::toString()
{
   return key + "=" + value;
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_ABSTRACTMAP_H */
