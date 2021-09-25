#ifndef UTIL_ABSTRACTCOLLECTION_H
#define UTIL_ABSTRACTCOLLECTION_H

#include <aro/util/Collection.h>

namespace aro {

namespace util {

template< class T> class AbstractCollection;

template< class T>
using RAbstarctCollection = Ref<AbstractCollection<T>>;

/**
 * AbstractCollection class template declaration
 */ 
template< class T>
class AbstractCollection : public Object, public virtual Collection<T>
{
   public:
      virtual vint size() = 0;
      virtual RIterator<T> iterator() = 0;
      
      virtual void clear();
      virtual vbool isEmpty();
      virtual RString toString();
      virtual RArray<T> toArray();
      virtual vbool add(Ref<T> e);
      virtual vbool remove(RObject o);
      virtual vbool contains(RObject o);
      virtual vbool addAll(RCollection<T> c);
      virtual vbool removeAll(RCollection<T> c);
      virtual vbool containsAll(RCollection<T> c);
   
   protected:
      AbstractCollection();
};


// AbstractCollection class template implementation

template <class T>
AbstractCollection<T>::AbstractCollection()
{
   
}

template <class T>
vbool AbstractCollection<T>::contains(RObject o)
{
   RIterator<T> e = iterator();

   if(o == nullref)
   {
      while(e->hasNext())
         if(e->next() == nullref)
            return true;
   }
   else
   {
      while(e->hasNext())
         if(o->equals(e->next()))
            return true;
   }
   
   return false;
}

template <class T>
vbool AbstractCollection<T>::isEmpty()
{
   return size() == 0;
}

template <class T>
RArray<T> AbstractCollection<T>::toArray()
{
   RArray<T> r = new Array<T>(size());
   
   RIterator<T> it = iterator();
   
   for(vint i=0; i<r->length; i++)
   {
      if(!it->hasNext())
         return r->copyOf(i);
      
      r[i] = it->next();
   }
   
   vint i = r->length;
   while(it->hasNext())
   {
      vint cap = r->length;
      
      if(i == cap)
      {
         vint newCap = ((cap/2)+1)*3;
         if(newCap <= cap)
         {
            if(cap == Int::MAX_VALUE)
               ex_throw new Exception("Required array size too large");
            
            newCap = Int::MAX_VALUE;
         }
         r = r->copyOf(newCap);
      }
      
      r[i++] = it->next();
   }
   
   return i == r->length ? r : r->copyOf(i);
}

template <class T>
vbool AbstractCollection<T>::add(Ref<T> e)
{
   ex_throw new UnsupportedException("add() not supported");
}

template <class T>
vbool AbstractCollection<T>::remove(RObject o)
{
   RIterator<T> e = iterator();
   
   if(o == nullref)
   {
      while(e->hasNext())
      {
         if(e->next() == nullref)
         {
            e->remove();
            return true;
         }
      }
   }
   else
   {
      while(e->hasNext())
      {
         if(o->equals(e->next()))
         {
            e->remove();
            return true;
         }
      }
   }
   
   return false;
}

template <class T>
vbool AbstractCollection<T>::containsAll(RCollection<T> c)
{
   RIterator<T> e = c->iterator();
   while(e->hasNext())
   {
      if(!contains(e->next()))
         return false;
   }
   
   return true;
}

template <class T>
vbool AbstractCollection<T>::addAll(RCollection<T> c)
{
   vbool modified = false;
   RIterator<T> e = c->iterator();
   while(e->hasNext())
   {
      if(add(e->next()))
         modified = true;
   }
   
   return modified;
}

template <class T>
vbool AbstractCollection<T>::removeAll(RCollection<T> c)
{
   vbool modified = false;
   RIterator<T> e = c->iterator();
   while(e->hasNext())
   {
      if(c->contains(e->next()))
      {
         e->remove();
         modified = true;
      }
   }
   
   return modified;
}

template <class T>
void AbstractCollection<T>::clear()
{
   RIterator<T> e = iterator();
   
   while(e->hasNext())
   {
      e->next();
      e->remove();
   }
}

template <class T>
RString AbstractCollection<T>::toString()
{
   RIterator<T> i = iterator();
   
   if(!i->hasNext())
      return "[]";
   
   RStringBuilder sb = new StringBuilder();

   sb->append("[");

   while(true)
   {
      RObject o = i->next();

      sb->append(o == thisref ? "(this collection)" : o);

      if(!i->hasNext())
         break;

      sb->append(", ");
   }
   
   return sb->append("]")->toString();
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_ABSTRACTCOLLECTION_H */
