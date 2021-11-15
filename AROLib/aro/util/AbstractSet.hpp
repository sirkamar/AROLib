#ifndef UTIL_ABSTRACTSET_H
#define UTIL_ABSTRACTSET_H

#include <aro/util/Set.hpp>
#include <aro/util/AbstractCollection.hpp>

namespace aro {

namespace util {

template <class T> class AbstractSet;

template <class T>
using RAbstractSet = Ref<AbstractSet<T>>;

/**
 * AbstractSet class template declaration
 */ 
template <class T>
class AbstractSet : public AbstractCollection<T>, public Set<T>
{
   public:
      virtual vint size()=0;
      virtual RIterator<T> iterator()=0;
      
      virtual vint hashCode();
      virtual vbool equals(RObject obj);
      virtual vbool removeAll(RCollection<T> c);

      virtual void clear() { AbstractCollection<T>::clear(); };
      virtual vbool isEmpty() { return AbstractCollection<T>::isEmpty(); };
      virtual vbool add(Ref<T> e) { return AbstractCollection<T>::add(e); };
      virtual RArray<T> toArray() { return AbstractCollection<T>::toArray(); };
      virtual vbool remove(RObject o) { return AbstractCollection<T>::remove(o); };
      virtual vbool contains(RObject o) { return AbstractCollection<T>::contains(o); };
      virtual vbool addAll(RCollection<T> c) { return AbstractCollection<T>::addAll(c); };
      virtual vbool containsAll(RCollection<T> c) { return AbstractCollection<T>::containsAll(c); };
   
   protected:
      AbstractSet();
};


// AbstractSet class template Implementation

template <class T>
AbstractSet<T>::AbstractSet()
{
   
}

template <class T>
vint AbstractSet<T>::hashCode()
{
   vint h = 0;

   RIterator<T> i = iterator();
   while(i->hasNext())
   {
      Ref<T> obj = i->next();
      if(obj != nullref)
         h += obj->hashCode();
   }

   return h;
}

template <class T>
vbool AbstractSet<T>::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(!type_of<Set<T>>(obj))
      return false;
   
   RCollection<T> c = type_cast<Collection<T>>(obj);
   if(c->size() != size())
      return false;
   
   ex_try
   {
      return containsAll(c);
   }
   ex_catch
   {
      ex_handle(NullException)
      {
         return false;
      }
   }
   ex_end
}

template <class T>
vbool AbstractSet<T>::removeAll(RCollection<T> c)
{
   vbool modified = false;
   
   if(size() > c->size())
   {
      for(RIterator<T> i = c->iterator(); i->hasNext(); )
         modified |= thisref->remove(i->next());
   }
   else
   {
      for(RIterator<T> i = c->iterator(); i->hasNext(); )
      {
         if(c->contains(i->next()))
         {
            i->remove();
            modified = true;
         }
      }
   }
   
   return modified;
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_ABSTRACTSET_H */
