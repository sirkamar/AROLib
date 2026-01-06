#ifndef UTIL_LINKEDLIST_H
#define UTIL_LINKEDLIST_H

#include <aro/util/AbstractList.hpp>

namespace aro {

namespace util {

template <class T> class LinkedList;

template <class T>
using RLinkedList = Ref<LinkedList<T>>;

/**
 A doubly-linked list implementation of the List interfaces.
 Implements all optional list operations, and permits all
 elements (including null).

 This class is a member of the AROLib Collections Framework.
 */
template <class T>
class LinkedList extends public AbstractList<T> implements Cloneable<LinkedList<T>>
{
   public:
      LinkedList();
      
      LinkedList(RCollection<T> c);
      
      virtual vint size(); // returns list size
      virtual void clear(); // clears the list
      virtual vbool isEmpty(); // checks if list is empty
      virtual RObject clone(); // returns a copy of this list
      virtual Ref<T> getLast(); // returns last element in list
      virtual Ref<T> getFirst(); // returns first element in list
      virtual Ref<T> removeLast(); // removes & returns last element in list
      virtual Ref<T> removeFirst(); // removes & returns first element in list
      virtual void addLast(Ref<T> e); // adds element to end of list
      virtual void addFirst(Ref<T> e); // adds element to front of list
      
      virtual RArray<T> toArray(); // Returns an array of all the list's elements
      virtual vbool add(Ref<T> e); // adds element to front of list
      virtual Ref<T> get(vint pos); // returns the indexed element of list
      virtual vbool remove(RObject e); // removes specified object from list
      virtual vint indexOf(RObject e); // returns first index of object in list or -1
      virtual RIterator<T> iterator(); // returns an iterator over the list
      virtual vbool contains(RObject e); // checks if list contains given object
      virtual Ref<T> remove(vint index); // removes and returns indexed element from list
      virtual vint lastIndexOf(RObject e); // returns last index of object in list or -1
      virtual void add(vint pos, Ref<T> e); // adds object at specifed index in list
      virtual vbool addAll(RCollection<T> c); // adds all the elements of c to list
      virtual Ref<T> set(vint pos, Ref<T> e); // replaces indexed element of list
      virtual RListIterator<T> listIterator(); // returns the ListIterator for list (index=0)
      virtual RListIterator<T> listIterator(vint pos); // returns the ListIterator for list (index)
      virtual vbool addAll(vint index, RCollection<T> c); // adds all the elements of c to list at index
   
   protected:
      // forward declaration
      class Node;
      typedef Ref<Node> RNode;

      // Node class for list elements
      class Node : public Object
      {
      public:
         Ref<T> data; // node's data
         RNode next; // next node
         RNode prev; // previous node

         Node(Ref<T>, RNode, RNode); // node constructor
      };

      Ref<T> unlink(RNode); // removes a node
      virtual void finalize(); // list finalizer
   
   private:
      vint count; // size of list
      RNode head; // the head of the list
      RNode tail; // the tail of the list
      
      RNode entry(vint); // retrieves a node
      void linkLast(Ref<T>); // adds new node at tail
      void linkFirst(Ref<T>); // adds new node at head
      Ref<T> unlinkLast(RNode); // removes node at tail
      Ref<T> unlinkFirst(RNode); // removes node at head
      RNode linkBefore(Ref<T>, RNode); // insets before node

      // A ListIterator for class list
      class ListItr : public Object, public ListIterator<T>
      {
         public:
            ListItr(RLinkedList<T>, vint); // ListItr constructor

            Ref<T> next(); // returns the next element in list
            void add(Ref<T>); // adds an object after the last returned
            void set(Ref<T>); // replaces the data value of last returned
            Ref<T> previous(); // returns the previous element in list
            void remove(); // removes last element returned by nextElement()
            vbool hasNext(); // checks if not at end of list
            vint nextIndex(); // returns the index of the next element
            vbool hasPrevious(); // checks if not at start of list
            vint previousIndex(); // returns the index of the previous element
         
         private:
            vint nxtIndex; // index of next node to be returned
            RNode cur, nxt; // the last, and next node returned
            RLinkedList<T> list; // reference to the backing list
            vint expectedModCount; // No. of list changes before iterator creation

            void checkForComodification(); // determines if backing list has changed
      };

   friend class ListItr;
};


// LinkedList class template implementation

template <class T>
LinkedList<T>::LinkedList()
{
   count = 0;
}

template <class T>
LinkedList<T>::LinkedList(RCollection<T> c)
{
   count = 0;
   
   addAll(c);
}

template <class T>
vbool LinkedList<T>::isEmpty()
{
   return count == 0;
}

template <class T>
RObject LinkedList<T>::clone()
{
    LinkedList<T> list = type_cast<LinkedList<T>>(AbstractList<T>::clone());

    list->head = list->tail = nullref;
    list->size = 0;
    list->modCount = 0;

    for(RNode x = head; x != nullref; x = x->next)
        list->add(x->data);

    return list;
}

template <class T>
Ref<T> LinkedList<T>::getFirst()
{
   if(head == nullref)
      ex_throw new StateException("No such element exists");
   
   return head->data;
}

template <class T>
Ref<T> LinkedList<T>::getLast()
{
   if(tail == nullref)
      ex_throw new StateException("No such element exists");
   
   return tail->data;
}

template <class T>
Ref<T> LinkedList<T>::removeFirst()
{
   if(head == nullref)
      ex_throw new StateException("No such element exists");
   
   return unlinkFirst(head);
}

template <class T>
Ref<T> LinkedList<T>::removeLast()
{
   if(tail == nullref)
      ex_throw new StateException("No such element exists");
   
   return unlinkLast(tail);
}

template <class T>
void LinkedList<T>::addFirst(Ref<T> obj)
{
   linkFirst(obj);
}

template <class T>
void LinkedList<T>::addLast(Ref<T> obj)
{
   linkLast(obj);
}

template <class T>
vbool LinkedList<T>::contains(RObject obj)
{
   return indexOf(obj) != -1;
}

template <class T>
vint LinkedList<T>::size()
{
   return count;
}

template <class T>
vbool LinkedList<T>::add(Ref<T> obj)
{
   linkLast(obj);
   return true;
}

template <class T>
vbool LinkedList<T>::remove(RObject obj)
{
   if(obj == nullref)
   {
      for(RNode n = head; n != nullref; n = n->next)
      {
         if(n->data == nullref)
         {
            unlink(n);
            return true;
         }
      }
   }
   else
   {
      for(RNode n = head; n != nullref; n = n->next)
      {
         if(obj->equals(n->data))
          {
             unlink(n);
             return true;
          }
      }
   }
   
   return false;
}

template <class T>
void LinkedList<T>::clear()
{
   // strictly unnecessary, but helps with ARM (garbage collection)
   for(RNode n = head; n != nullref; )
   {
      RNode next = n->next;
      n->data = nullref;
      n->next = nullref;
      n->prev = nullref;
      n = next;
   }

   head = tail = nullref;
   
   count = 0;
   modCount++;
}

template <class T>
Ref<T> LinkedList<T>::get(vint index)
{
   return entry(index)->data;
}

template <class T>
Ref<T> LinkedList<T>::set(vint index, Ref<T> obj)
{
   RNode n = entry(index);
   Ref<T> oldVal = n->data;
   n->data = obj;
   return oldVal;
}

template <class T>
void LinkedList<T>::add(vint index, Ref<T> obj)
{
   if(index == count)
      linkLast(obj);
   else
      linkBefore(obj, entry(index));
}

template <class T>
Ref<T> LinkedList<T>::remove(vint index)
{
   return unlink(entry(index));
}

template <class T>
vint LinkedList<T>::indexOf(RObject obj)
{
   vint index = 0;
   if(obj == nullref)
   {
      for(RNode n = head; n != nullref; n = n->next)
      {
         if(n->data == nullref)
            return index;
         
         index++;
      }
   }
   else
   {
      for(RNode n = head; n != head; n = n->next)
      {
         if(obj->equals(n->data))
            return index;
         
         index++;
      }
   }
   
   return -1;
}

template <class T>
vint LinkedList<T>::lastIndexOf(RObject obj)
{
   vint index = count;
   if(obj == nullref)
   {
      for(RNode n = tail; n != nullref; n = n->prev)
      {
         index--;
         if(n->data == nullref)
            return index;
      }
   }
   else
   {
      for(RNode n = tail; n != nullref; n = n->prev)
      {
         index--;
         if(obj->equals(n->data))
            return index;
      }
   }
   
   return -1;
}

template <class T>
RArray<T> LinkedList<T>::toArray()
{
   vint i = 0; // array indexer
   RArray<T> arr = new Array<T>(count);
   
   for(RNode n = head; n != nullref; n = n->next)
      arr[i++] = n->data;
   
   return arr;
}

template <class T>
vbool LinkedList<T>::addAll(RCollection<T> c)
{
   return addAll(count, c);
}

template <class T>
vbool LinkedList<T>::addAll(vint index, RCollection<T> c)
{
   if(index < 0 || index >= count)
      ex_throw new IndexException("List Index out of bounds: ", index);
   
   RArray<T> a = c->toArray();
   vint numNew = a->length;
   if(numNew == 0)
      return false;
   
   modCount++;
   
   RNode successor, predecessor;
   if(index == count)
   {
      successor = nullref;
      predecessor = tail;
   }
   else
   {
      successor = entry(index);
      predecessor = successor->prev;
   }

   for(Ref<T> obj : a)
   {
      RNode n = new Node(obj, nullref, predecessor);

      if(predecessor == nullref)
         head = n;
      else
         predecessor->next = n;

      predecessor = n;
   }

   if(successor == nullref)
      tail = predecessor;
   else
   {
      predecessor->next = successor;
      successor->prev = predecessor;
   }
   
   count += numNew;
   modCount++;
   return true;
}

template <class T>
void LinkedList<T>::finalize()
{
   if(!System::isFinalizing())
      clear(); // clear list
   
   AbstractList<T>::finalize();
}

template <class T>
RIterator<T> LinkedList<T>::iterator()
{
   return listIterator();
}

template <class T>
RListIterator<T> LinkedList<T>::listIterator()
{
   return listIterator(0);
}

template <class T>
RListIterator<T> LinkedList<T>::listIterator(vint index)
{
   return new ListItr(thisref, index);
}

template <class T>
void LinkedList<T>::linkLast(Ref<T> obj)
{
   RNode t = tail;
   RNode n = new Node(obj, nullref, t);
   
   tail = n;
   
   if(t == nullref)
      head = n;
   else
      t->next = n;
   
   count++;
   modCount++;
}

template <class T>
void LinkedList<T>::linkFirst(Ref<T> obj)
{
   RNode h = head;
   RNode n = new Node(obj, h, nullref);

   head = n;

   if(h == nullref)
      tail = n;
   else
      h->prev = n;

   count++;
   modCount++;
}

template <class T>
Ref<T> LinkedList<T>::unlink(typename LinkedList<T>::RNode n)
{
   Ref<T> obj = n->data;
   RNode next = n->next;
   RNode prev = n->prev;

   if(prev == nullref)
      head = next;
   else
   {
      prev->next = next;
      n->prev = nullref;
   }

   if(next == nullref)
      tail = prev;
   else
   {
      next->prev = prev;
      n->next = nullref;
   }

   n->data = nullref;

   count--;
   modCount++;
   return obj;
}

template <class T>
Ref<T> LinkedList<T>::unlinkLast(typename LinkedList<T>::RNode n)
{
   Ref<T> obj = n->data;
   RNode prev = n->prev;

   n->data = nullref;
   n->prev = nullref;

   tail = prev;

   if(prev == nullref)
      head = nullref;
   else
      prev->next = nullref;

   count--;
   modCount++;

   return obj;
}

template <class T>
Ref<T> LinkedList<T>::unlinkFirst(typename LinkedList<T>::RNode n)
{
   Ref<T> obj = head->data;
   RNode next = head->next;

   n->data = nullref;
   n->next = nullref;

   head = next;

   if(next == nullref)
      tail = nullref;
   else
      next->prev = nullref;

   count--;
   modCount++;

   return obj;
}

template <class T>
typename LinkedList<T>::RNode LinkedList<T>::entry(vint index)
{
   if(index < 0 || index >= count)
      ex_throw new IndexException("List Index out of bounds: ", index);
   
   RNode n;
   if(index < (count >> 1))
   {
      n = head;
      for(vint i = 0; i < index; i++)
         n = n->next;
   }
   else
   {
      n = tail;
      for(vint i = count-1; i > index; i--)
         n = n->prev;
   }
   
   return n;
}

template <class T>
typename LinkedList<T>::RNode LinkedList<T>::linkBefore(Ref<T> obj, typename LinkedList<T>::RNode n)
{
   if(obj == thisref)
      ex_throw new ArgumentException("Cannot add list to itself");
   
   RNode prev = n->prev;
   RNode newEntry = new Node(obj, n, prev);

   n->prev = newEntry;

   if(prev == nullref)
      head = newEntry;
   else
      prev->next = newEntry;
   
   count++;
   modCount++;
   
   return newEntry;
}

template <class T>
LinkedList<T>::Node::Node(Ref<T> dta, typename LinkedList<T>::RNode nxt, typename LinkedList<T>::RNode pre)
{
   data = dta; next = nxt; prev = pre;
}

template <class T>
LinkedList<T>::ListItr::ListItr(RLinkedList<T> lst, vint start)
{
   if(start < 0 || start > lst->count)
      ex_throw new IndexException("List Index out of bounds: " , start);
   
   list = lst;
   expectedModCount = list->modCount;
   
   nxt = (start == list->count) ? nullref : list->entry(start);
   nxtIndex = start;
}

template <class T>
Ref<T> LinkedList<T>::ListItr::next()
{
   checkForComodification();
   
   if(!hasNext())
      ex_throw new StateException("No next element");
   
   cur = nxt;
   nxtIndex++;
   nxt = nxt->next;
   
   return cur->data;
}

template <class T>
void LinkedList<T>::ListItr::remove()
{
   checkForComodification();
   
   if(cur == nullref)
      ex_throw new StateException("No element to remove");

   RNode curNext = cur->next;
   
   list->unlink(cur); // may throw exception
   
   if(nxt == cur)
      nxt = curNext;
   else
      nxtIndex--;
   
   cur = nullref;
   expectedModCount++;
}

template <class T>
Ref<T> LinkedList<T>::ListItr::previous()
{
   checkForComodification();
   
   if(!hasPrevious())
      ex_throw new StateException("No previous element");
   
   cur = nxt = (nxt == nullref) ? list->tail : nxt->prev;
   nxtIndex--;
   
   return cur->data;
}

template <class T>
void LinkedList<T>::ListItr::add(Ref<T> obj)
{
   checkForComodification();
   
   cur = nullref;
   
   if(nxt == nullref)
      list->linkLast(obj);
   else
      list->linkBefore(obj, nxt);

   nxtIndex++;
   expectedModCount++;
}

template <class T>
void LinkedList<T>::ListItr::set(Ref<T> obj)
{
   if(cur == nullref)
      ex_throw new StateException("No element to set");
   
   checkForComodification();
   
   cur->data = obj;
}

template <class T>
vbool LinkedList<T>::ListItr::hasNext()
{
   return nxtIndex < list->count;
}

template <class T>
vint LinkedList<T>::ListItr::nextIndex()
{
   return nxtIndex;
}

template <class T>
vbool LinkedList<T>::ListItr::hasPrevious()
{
   return nxtIndex > 0;
}

template <class T>
vint LinkedList<T>::ListItr::previousIndex()
{
   return nxtIndex-1;
}

template <class T>
void LinkedList<T>::ListItr::checkForComodification()
{
   if(expectedModCount != list->modCount)
      ex_throw new StateException("concurrent modification");
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_LINKEDLIST_H */
