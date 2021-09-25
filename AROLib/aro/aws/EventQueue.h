#ifndef AWS_EVENTQUEUE_H
#define AWS_EVENTQUEUE_H

#include <aro/aws/AWSEvent.h>
#include <aro/aws/EventDispatcher.h>

namespace aro {

namespace aws{

namespace event {
class PaintEvent;
typedef Ref<PaintEvent> RPaintEvent;
}

class EventQueue;
typedef Ref<EventQueue> REventQueue;

class EventQueue : public Object
{
   class QueueItem;
   typedef Ref<QueueItem> RQueueItem;
   
   class Queue;
   typedef Ref<Queue> RQueue;
   
   public:
      EventQueue();
      
      void postEvent(RAWSEvent e);
      
      virtual RAWSEvent peekEvent();
      
      virtual RAWSEvent getNextEvent();
      
      static RAWSEvent getCurrentEvent();
      
      static vlong getMostRecentEventTime();

      static void setCurrentEventAndMostRecentTime(RAWSEvent e);
   
   protected:
      void dispatchEvent(RAWSEvent e);

   private:   
      vbool noEvents();

      void initDispatcher();

      void detachDispatcher();

      static vint nextThreadNumber();
      
      RAWSEvent getCurrentEventImpl();
      
      REventDispatcher getDispatcher();
      
      vlong getMostRecentEventTimeImpl();
      
      void cacheEQItem(RQueueItem entry);

      void uncacheEQItem(RQueueItem entry);

      static vint getPriority(RAWSEvent e);
      
      static int eventToCacheIndex(RAWSEvent e);
      
      void postEvent(RAWSEvent e, vint priority);

      void setCurrentEventAndMostRecentTimeImpl(RAWSEvent e);

      event::RPaintEvent mergePaintEvents(event::RPaintEvent a, event::RPaintEvent b);

      vbool coalesceEvent(RAWSEvent e, vint priority);

      vbool coalescePaintEvent(event::RPaintEvent e);

      static const vint NUM_PRIORITIES;
      static const vint HIGH_PRIORITY;
      static const vint NORM_PRIORITY;
      static const vint LOW_PRIORITY;
      
      RWeak<AWSEvent> currentEvent;
      
      static const vint CACHE_SIZE;
      
      static vint threadInitNumber;

      REventDispatcher dispatcher;
      
      vlong mostRecentEventTime;
      
      RArray<Queue> queues;
      
      const RString name;
      
      friend class Component;
      friend class EventDispatcher;
      friend class DefaultFocusManager;
};

class EventQueue::QueueItem : public Object
{
   public:
      vint id;
      RAWSEvent evnt;
      RQueueItem next;
      
      QueueItem(RAWSEvent e);
};
   
class EventQueue::Queue : public Object
{
   public:
      RQueueItem head;
      RQueueItem tail;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_EVENTQUEUE_H */
