#ifndef AWS_LISTENERLIST_H
#define AWS_LISTENERLIST_H

#include <aro/core.hpp>
#include <aro/util/Listener.hpp>
#include <aro/util/ArrayList.hpp>

namespace aro {

namespace aws {

class ListenerList;
typedef Ref<ListenerList> RListenerList;

class ListenerList : public Object
{
   public:
      ListenerList();
      
      vint getListenerCount();
      
      RArray<util::Listener> getListeners();
      
      template <class T> vint getListenerCount();
      
      template <class T> void add(Ref<T> listener);
      
      template <class T> void remove(Ref<T> listener);
      
      template <class T> RArray<T> getListeners();
   
   private:
      util::RArrayList<util::Listener> listeners;
};


template <class T>
vint ListenerList::getListenerCount()
{
   vint count = 0;

   for_each(util::RListener l, listeners)
   {
      if(type_of<T>(l))
         count++;
   }

   return count;
}

template <class T>
void ListenerList::add(Ref<T> listener)
{
   sync_lock(thisref)
   {
      if (listener == nullref)
         return;
      
      listeners->add(listener);
   }
}

template <class T>
void ListenerList::remove(Ref<T> listener)
{
   sync_lock(thisref)
   {
      if (listener == nullref)
         return;
      
      listeners->remove(listener);
   }
}

template <class T>
RArray<T> ListenerList::getListeners()
{
   util::RIterator<util::Listener> it = listeners->iterator();

   util::RList<T> tList = new util::ArrayList<T>();

   while(it->hasNext())
   {
      util::RListener lsnr = it->next();

      if(type_of<T>(lsnr))
         tList->add(type_cast<T>(lsnr));
   }

   return tList->toArray();

   //RArray<T> arr = new Array<T>(getListenerCount<T>());
   //
   //vint arrIndex = 0;
   //
   //RIterable<util::Listener> it = listeners;
   //
   //for_each(util::RListener l, listeners)
   //{
   //   if(type_of<T>(l))
   //   {
   //      arr[arrIndex++] = type_cast<T>(l);
   //   }
   //}
   //
   //return arr;
}

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_LISTENERLIST_H */
