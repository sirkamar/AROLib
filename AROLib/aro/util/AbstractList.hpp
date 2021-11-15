#ifndef UTIL_ABSTRACTLIST_H
#define UTIL_ABSTRACTLIST_H

#include <aro/util/List.hpp>
#include <aro/util/AbstractCollection.hpp>

namespace aro {

namespace util {

template <class T> class SubList;

template <class T> class AbstractList;

template< class T>
using RAbstractList = Ref<AbstractList<T>>;

/**
 * AbstractList class template declaration
 */ 
template <class T>
class AbstractList : public AbstractCollection<T>, public List<T>
{
   class Itr : public Object, public Iterator<T>
   {
      public:
         Itr(RAbstractList<T> lst);
         
         virtual vbool hasNext();
         virtual void remove();
         virtual Ref<T> next();
      
      protected:
         vint cursor, lastRet;
         vint expectedModCount;
         RAbstractList<T> list;
         
         void checkForComodification();
   };
   
   class ListItr : public Itr, public ListIterator<T>
   {
      public:
         ListItr(RAbstractList<T> lst, vint index);
         
         virtual vbool hasNext();
         virtual Ref<T> next();
         
         virtual vbool hasPrevious();
         virtual Ref<T> previous();
         
         virtual vint nextIndex();
         virtual vint previousIndex();
         
         virtual void remove();
         virtual void set(Ref<T> obj);
         virtual void add(Ref<T> obj);
   };
   
   class SubList;

   friend class Itr;
   friend class ListItr;
   friend class SubList;
   
   public:
      virtual vint size()=0;
      virtual Ref<T> get(vint index)=0;
      
      virtual void clear();
      virtual vbool isEmpty();
      virtual RArray<T> toArray();
      virtual vbool add(Ref<T> obj);
      virtual vbool remove(RObject o);
      virtual vint indexOf(RObject o);
      virtual RIterator<T> iterator();
      virtual Ref<T> remove(vint index);
      virtual vbool equals(RObject obj);
      virtual vbool contains(RObject o);
      virtual vint lastIndexOf(RObject o);
      virtual void add(vint index, Ref<T> obj);
      virtual Ref<T> set(vint index, Ref<T> obj);

      virtual vbool addAll(RCollection<T> c);
      virtual RListIterator<T> listIterator();
      virtual vbool removeAll(RCollection<T> c);
      virtual vbool containsAll(RCollection<T> c);
      virtual vbool addAll(vint index, RCollection<T> c);
      virtual RListIterator<T> listIterator(vint index);
      virtual RList<T> sublist(vint fromIndex, vint toIndex);
   
   protected:
      vint modCount;
      
      AbstractList();
      
      virtual void removeRange(vint fromIndex, vint toIndex);
};

// AbstractList class template implementation

template <class T>
class AbstractList<T>::SubList : public AbstractList<T>
{
   class SubListItr : public Object, public ListIterator<T>
   {
      public:
         SubListItr(Ref<SubList> rs, RListIterator<T> it)
            :s(rs), i(it){}
         
         vbool hasNext()
         {
            return nextIndex() < s->count;
         }
         
         Ref<T> next()
         {
            if(hasNext())
               return i->next();
            else
               ex_throw new StateException("no such element");
         }
         
         vbool hasPrevious()
         {
            return previousIndex() >= 0;
         }
         
         Ref<T> previous()
         {
            if(hasPrevious())
               return i->previous();
            else
               ex_throw new StateException("no such element");
         }
         
         vint nextIndex()
         {
            return i->nextIndex()-s->offset;
         }
         
         vint previousIndex()
         {
            return i->previousIndex()-s->offset;
         }
         
         void remove()
         {
            i->remove();
            s->expectedModCount = s->l->modCount;
            s->count--; s->l->modCount++;
         }
         
         void set(Ref<T> obj)
         {
            i->set(obj);
         }
         
         void add(Ref<T> obj)
         {
            i->add(obj);
            s->expectedModCount = s->l->modCount;
            s->count++; s->l->modCount++;
         }
      
      private:
         Ref<SubList> s;
         RListIterator<T> i;
   };
   
   friend class SubListItr;
   
   public:      
      Ref<T> set(vint index, Ref<T> obj)
      {
         rangeCheck(index);
         checkForComodification();
         return l->set(index+offset, obj);
      }
      
      Ref<T> get(vint index)
      {
         rangeCheck(index);
         checkForComodification();
         return l->get(index+offset);
      }
      
      vint size()
      {
         checkForComodification();
         return count;
      }
      
      void add(vint index, Ref<T> obj)
      {
         if(index < 0 || index > count)
            ex_throw new IndexException();
         
         checkForComodification();
         l->add(index+offset, obj);
         expectedModCount = l->modCount;
         count++; l->modCount++;
      }
      
      Ref<T> remove(vint index)
      {
         rangeCheck(index);
         checkForComodification();
         Ref<T> obj = l->remove(index+offset);
         expectedModCount = l->modCount;
         count--; l->modCount++;
         return obj;
      }
      
      RIterator<T> iterator()
      {
         return listIterator(0);
      }
      
      RListIterator<T> listIterator(vint index)
      {
         checkForComodification();
         if(index<0 || index>count)
            ex_throw new IndexException("Index: "+
               String::valueOf(index)+", Size: "+String::valueOf(count));
         
         return new SubListItr(thisref, l->listIterator(index+offset));
      }
      
      RList<T> sublist(vint fromIndex, vint toIndex)
      {
         return new SubList(thisref, fromIndex, toIndex);
      }
   
   protected:
      void removeRange(vint fromIndex, vint toIndex)
      {
         checkForComodification();
         l->removeRange(fromIndex+offset, toIndex+offset);
         expectedModCount = l->modCount;
         count -= (toIndex - fromIndex);
         l->modCount++;
      }
   
   private:
      vint offset, count;
      RAbstractList<T> l;
      vint expectedModCount;

      SubList(RAbstractList<T> lst, vint fromIndex, vint toIndex)
      {
         if(fromIndex < 0)
            ex_throw new IndexException("fomIndex =", fromIndex);
         if(toIndex > lst->size())
            ex_throw new IndexException("toIndex = ", toIndex);
         if(fromIndex > toIndex)
            ex_throw new ArgumentException("fromIndex(" +
                     String::valueOf(fromIndex) + ") > toIndex(" +
                     String::valueOf(toIndex) + ")");
         
         l = lst;
         offset = fromIndex;
         count = toIndex - fromIndex;
         expectedModCount = l->modCount;
      }

      void rangeCheck(vint index)
      {
         if(index<0 || index>=count)
            ex_throw new IndexException("Index: "+
               String::valueOf(index)+", Size: "+String::valueOf(count));
      }
      
      void checkForComodification()
      {
         if(l->modCount != expectedModCount)
            ex_throw new StateException("concurrent modification");
      }
   
   friend class AbstractList<T>;
};

template <class T>
AbstractList<T>::AbstractList()
{
   modCount = 0;
}

template <class T>
vbool AbstractList<T>::add(Ref<T> obj)
{
   add(size(), obj);
   
   return true;
}

template <class T>
vbool AbstractList<T>::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(!type_of<List<Object>>(obj))
      return false;
   
   RListIterator<T> e1 = listIterator();
   RListIterator<Object> e2 = type_cast<List<Object>>(obj)->listIterator();
   
   while(e1->hasNext() && e2->hasNext())
   {
      Ref<T> o1 = e1->next();
      RObject o2 = e2->next();
      
      if(!(o1==nullref ? o2==nullref : o2->equals(o1)))
         return false;
   }
   
   return !(e1->hasNext() || e2->hasNext());
}

template <class T>
vbool AbstractList<T>::contains(RObject obj)
{
   RIterator<T> e = iterator();
   if(obj == nullref)
   {
      while(e->hasNext())
         if(e->next() == nullref)
            return true;
   }
   else
   {
      while(e->hasNext())
         if(obj->equals(e->next()))
            return true;
   }
   
   return false;
}

template <class T>
Ref<T> AbstractList<T>::set(vint index, Ref<T> obj)
{
   ex_throw new UnsupportedException();
}

template <class T>
void AbstractList<T>::add(vint index, Ref<T> obj)
{
   ex_throw new UnsupportedException();
}

template <class T>
Ref<T> AbstractList<T>::remove(vint index)
{
   ex_throw new UnsupportedException();
}

template <class T>
vbool AbstractList<T>::remove(RObject obj)
{
   RIterator<T> e = iterator();
   if(obj == nullref)
   {
      while(e->hasNext())
         if(e->next() == nullref)
         {
            e->remove();
            return true;
         }
   }
   else
   {
      while(e->hasNext())
         if(obj->equals(e->next()))
         {
            e->remove();
            return true;
         }
   }
   
   return false;
}

template <class T>
vint AbstractList<T>::indexOf(RObject obj)
{
   RListIterator<T> e = listIterator();
   
   if(obj == nullref)
   {
      while(e->hasNext())
      {
         if(e->next() == nullref)
            return e->previousIndex();
      }
   }
   else
   {
      while(e->hasNext())
      {
         if(obj->equals(e->next()))
            return e->previousIndex();
      }
   }
   
   return -1;
}

template <class T>
vint AbstractList<T>::lastIndexOf(RObject obj)
{
   RListIterator<T> e = listIterator(size());
   
   if(obj == nullref)
   {
      while(e->hasPrevious())
      {
         if(e->previous() == nullref)
            return e->nextIndex();
      }
   }
   else
   {
      while(e->hasPrevious())
      {
         if(obj->equals(e->previous()))
            return e->nextIndex();
      }
   }
   
   return -1;
}

template <class T>
vbool AbstractList<T>::addAll(RCollection<T> c)
{
   return AbstractCollection<T>::addAll(c);
}

template <class T>
vbool AbstractList<T>::removeAll(RCollection<T> c)
{
   return AbstractCollection<T>::removeAll(c);
}

template <class T>
vbool AbstractList<T>::containsAll(RCollection<T> c)
{
   return AbstractCollection<T>::containsAll(c);
}

template <class T>
vbool AbstractList<T>::addAll(vint index, RCollection<T> c)
{
   vbool modified = false;
   RIterator<T> e = c->iterator();
   while(e->hasNext())
   {
      add(index++, e->next());
      modified = true;
   }
   
   return modified;
}

template <class T>
vbool AbstractList<T>::isEmpty()
{
   return size() == 0;
}

template <class T>
void AbstractList<T>::clear()
{
   removeRange(0, size());
}

template <class T>
RIterator<T> AbstractList<T>::iterator()
{
   return new Itr(thisref);
}

template <class T>
RArray<T> AbstractList<T>::toArray()
{
   RArray<T> arr = new Array<T>(size());
   RIterator<T> it = iterator();
   
   for(vint i=0; i<arr->length; i++)
   {
      if(!it->hasNext())
         return arr->copyOf(i);
      
      arr[i] = it->next();
   }
   
   return arr;
}

template <class T>
RListIterator<T> AbstractList<T>::listIterator()
{
   return listIterator(0);
}

template <class T>
RListIterator<T> AbstractList<T>::listIterator(vint index)
{
   if(index < 0 || index > size())
      ex_throw new IndexException("Index: ", index);
   
   return new ListItr(thisref, index);
}

template <class T>
RList<T> AbstractList<T>::sublist(vint fromIndex, vint toIndex)
{
   return new SubList(thisref, fromIndex, toIndex);
}

template <class T>
void AbstractList<T>::removeRange(vint fromIndex, vint toIndex)
{
   RListIterator<T> it = listIterator(fromIndex);
   
   for(vint i=0, n=toIndex-fromIndex; i<n; i++)
   {
      it->next();
      it->remove();
   }
}

template <class T>
AbstractList<T>::Itr::Itr(RAbstractList<T> lst)
   :list(lst)
{
   cursor = 0;
   lastRet = -1;
   expectedModCount = list->modCount;
}

template <class T>
vbool AbstractList<T>::Itr::hasNext()
{
   return cursor != list->size();
}

template <class T>
Ref<T> AbstractList<T>::Itr::next()
{
   checkForComodification();
   
   ex_try
   {
      Ref<T> next = list->get(cursor);
      lastRet = cursor++;
      return next;
   }
   ex_catch
   {
      ex_handle(IndexException)
	   {
		  checkForComodification();
      
		  ex_throw new StateException("no next element");
	   }
   }
   ex_end
}

template <class T>
void AbstractList<T>::Itr::remove()
{
   if(lastRet == -1)
      ex_throw new StateException();
   
   checkForComodification();
   
   ex_try
   {
      list->remove(lastRet);
      if(lastRet < cursor)
         cursor--;
      
      lastRet = -1;
      
      expectedModCount = list->modCount;
   }
   ex_catch
   {
      ex_handle(IndexException)
	   {
		  ex_throw new StateException("concurrent modification");
	   }
   }
   ex_end
}

template <class T>
void AbstractList<T>::Itr::checkForComodification()
{
   if(list->modCount != expectedModCount)
      ex_throw new StateException("concurrent modification");
}

template <class T>
AbstractList<T>::ListItr::ListItr(RAbstractList<T> lst, vint index)
   :Itr(lst)
{
   cursor = index;
}

template <class T>
vbool AbstractList<T>::ListItr::hasNext()
{
   return Itr::hasNext();
}

template <class T>
Ref<T> AbstractList<T>::ListItr::next()
{
   return Itr::next();
}

template <class T>
vbool AbstractList<T>::ListItr::hasPrevious()
{
   return cursor != 0;
}

template <class T>
Ref<T> AbstractList<T>::ListItr::previous()
{
   checkForComodification();
   
   ex_try
   {
      vint i = cursor-1;
      Ref<T> e = list->get(i);
      lastRet = cursor = i;
      return e;
   }
   ex_catch
   {
      ex_handle(IndexException)
	   {
		  checkForComodification();
      
		  ex_throw new StateException("no previous element");
	   }
   }
   ex_end
}

template <class T>
vint AbstractList<T>::ListItr::nextIndex()
{
   return cursor;
}

template <class T>
vint AbstractList<T>::ListItr::previousIndex()
{
   return cursor - 1;
}

template <class T>
void AbstractList<T>::ListItr::remove()
{
   Itr::remove();
}

template <class T>
void AbstractList<T>::ListItr::set(Ref<T> obj)
{
   if(lastRet == -1)
      ex_throw new StateException();
   
   checkForComodification();
   
   ex_try
   {
      list->set(lastRet, obj);
      expectedModCount = list->modCount;
   }
   ex_catch
   {
      ex_handle(IndexException)
	   {
		  ex_throw new StateException("concurrent modification");
	   }
   }
   ex_end
}

template <class T>
void AbstractList<T>::ListItr::add(Ref<T> obj)
{
   checkForComodification();
   
   ex_try
   {
      list->add(cursor++, obj);
      lastRet = -1;
      expectedModCount = list->modCount;
   }
   ex_catch
   {
      ex_handle(IndexException)
	   {
		  ex_throw new StateException("concurrent modification");
	   }
   }
   ex_end
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_ABSTRACTLIST_H */
