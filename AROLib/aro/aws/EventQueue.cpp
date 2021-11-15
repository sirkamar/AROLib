#include <aro/core.hpp>
#include <aro/core/Long.hpp>
#include <aro/core/System.hpp>
#include <aro/aws/Component.hpp>
#include <aro/aws/Rectangle.hpp>
#include <aro/aws/EventQueue.hpp>
#include <aro/aws/event/InputEvent.hpp>
#include <aro/aws/event/PaintEvent.hpp>
#include <aro/aws/event/ActionEvent.hpp>
#include <aro/aws/EventDispatcher.hpp>

namespace aro {

namespace aws {

using namespace event;

vint EventQueue::threadInitNumber = 0;

const vint EventQueue::CACHE_SIZE = 2;

const vint EventQueue::LOW_PRIORITY = 0;
const vint EventQueue::NORM_PRIORITY = 1;
const vint EventQueue::HIGH_PRIORITY = 2;
const vint EventQueue::NUM_PRIORITIES = 3;

EventQueue::EventQueue()
   :name("AWS-EventQueue-" + String::valueOf(nextThreadNumber()))
{
   mostRecentEventTime = System::currentTime();
   
   queues = new Array<Queue>(NUM_PRIORITIES);
   
   for(vint n=0; n<NUM_PRIORITIES; n++)
      queues[n] = new Queue();
}

vint EventQueue::nextThreadNumber()
{
   return threadInitNumber++;
}

void EventQueue::postEvent(RAWSEvent e)
{
   e->isPosted = true;

   sync_lock(thisref)
   {
      postEvent(e, getPriority(e));
      
      if(dispatcher == nullref)
         initDispatcher();
   }
}

int EventQueue::getPriority(RAWSEvent e)
{
   vint id = e->getEventID();
   
   if(id == PaintEvent::PAINT || id == PaintEvent::UPDATE)
      return LOW_PRIORITY;
   
   return NORM_PRIORITY;
}

void EventQueue::postEvent(RAWSEvent e, vint priority)
{
   RObject source = e->getSource();

   if(coalesceEvent(e, priority))
      return;

   RQueueItem newItem = new QueueItem(e);

   cacheEQItem(newItem);

   if(queues[priority]->head == nullref)
   {
      queues[priority]->head = queues[priority]->tail = newItem;
   }
   else
   {
      queues[priority]->tail->next = newItem;
      queues[priority]->tail = newItem;
   }
}

vbool EventQueue::coalescePaintEvent(RPaintEvent e)
{
   RArray<QueueItem> cache = type_cast<Component>(e->getSource())->eventCache;

   if(cache == nullref)
      return false;

   vint index = eventToCacheIndex(e);

   if(index != -1 && cache[index] != nullref)
   {
      RPaintEvent merged = mergePaintEvents(e, type_cast<PaintEvent>(cache[index]->evnt));

      if(merged != nullref)
      {
         cache[index]->evnt = merged;
         return true;
      }
   }

   return false;
}

RPaintEvent EventQueue::mergePaintEvents(RPaintEvent a, RPaintEvent b)
{
   RRectangle aRect = a->getUpdateRect();
   RRectangle bRect = b->getUpdateRect();
   
   if(bRect->contains(aRect))
      return b;
   
   if(aRect->contains(bRect))
      return a;
   
   return nullref;
}

vbool EventQueue::coalesceEvent(RAWSEvent e, vint priority)
{
   if(!type_of<Component>(e->getSource()))
      return false;

   if(type_of<PaintEvent>(e))
      return coalescePaintEvent(type_cast<PaintEvent>(e));

   return false;
}

void EventQueue::cacheEQItem(EventQueue::RQueueItem entry)
{
   vint index = eventToCacheIndex(entry->evnt);

   if(index != -1 && type_of<Component>(entry->evnt->getSource()))
   {
      RComponent source = type_cast<Component>(entry->evnt->getSource());

      if(source->eventCache == nullref)
         source->eventCache = new Array<QueueItem>(CACHE_SIZE);

      source->eventCache[index] = entry;
   }
}

void EventQueue::uncacheEQItem(EventQueue::RQueueItem entry)
{
   vint index = eventToCacheIndex(entry->evnt);

   if(index != -1 && type_of<Component>(entry->evnt->getSource()))
   {
      RComponent source = type_cast<Component>(entry->evnt->getSource());

      if(source->eventCache == nullref)
         return;

      source->eventCache[index] = nullref;
   }
}

int EventQueue::eventToCacheIndex(RAWSEvent e)
{
   vint id = e->getEventID();

   if(id == PaintEvent::PAINT)
      return 0;

   if(id == PaintEvent::UPDATE)
      return 1;

   return -1;
}

vbool EventQueue::noEvents()
{
   for(vint i=0; i<NUM_PRIORITIES; i++)
   {
      if(queues[i]->head != nullref)
         return false;
   }

   return true;
}

RAWSEvent EventQueue::getNextEvent()
{
   //do
   {
      sync_lock(thisref)
      {
         for(vint i=NUM_PRIORITIES-1; i>=0; i--)
         {
            if(queues[i]->head != nullref)
            {
               RQueueItem entry = queues[i]->head;

               queues[i]->head = entry->next;

               if(entry->next == nullref)
                  queues[i]->tail = nullref;

               uncacheEQItem(entry);

               return entry->evnt;
            }
         }
      }
   }
   //while(true);

   return nullref;
}

RAWSEvent EventQueue::peekEvent()
{
   sync_lock(thisref)
   {
      for(vint i=NUM_PRIORITIES-1; i>=0; i--)
         if(queues[i]->head != nullref)
            return queues[i]->head->evnt;
   }
   
   return nullref;
}

void EventQueue::dispatchEvent(RAWSEvent e)
{
   e->isPosted = true;

   RObject src = e->getSource();

   if(type_of<Component>(src))
      type_cast<Component>(src)->dispatchEvent(e);
   else
      System::err->println("unable to dispatch event: " + e);
}

REventDispatcher EventQueue::getDispatcher()
{
   return dispatcher;
}

void EventQueue::detachDispatcher()
{
   dispatcher = nullref;
}

void EventQueue::initDispatcher()
{
   dispatcher = new EventDispatcher(name, thisref);
   
   dispatcher->start();
   
   dispatcher->setPriority(Thread::PRIORITY_ABOVE_NORMAL);
}

RAWSEvent EventQueue::getCurrentEvent()
{
   return System::getEventQueue()->getCurrentEventImpl();
}

vlong EventQueue::getMostRecentEventTime()
{
   return System::getEventQueue()->getMostRecentEventTimeImpl();
}

RAWSEvent EventQueue::getCurrentEventImpl()
{
   sync_lock(thisref)
   {
      return currentEvent->get();
   }
}

vlong EventQueue::getMostRecentEventTimeImpl()
{
   sync_lock(thisref)
   {
      return mostRecentEventTime;
   }
}

void EventQueue::setCurrentEventAndMostRecentTime(RAWSEvent e)
{
   System::getEventQueue()->setCurrentEventAndMostRecentTimeImpl(e);
}

void EventQueue::setCurrentEventAndMostRecentTimeImpl(RAWSEvent e)
{
   sync_lock(thisref)
   {
      currentEvent = new Weak<AWSEvent>(e);

      vlong mostRecentEventTime2 = Long::MIN_VALUE;

      if(type_of<InputEvent>(e))
      {
         RInputEvent ie = type_cast<InputEvent>(e);

         mostRecentEventTime2 = ie->getWhen();
      }
      else if(type_of<ActionEvent>(e))
      {
         RActionEvent ae = type_cast<ActionEvent>(e);

         mostRecentEventTime2 = ae->getWhen();
      }

      mostRecentEventTime = Math::maximum(mostRecentEventTime, mostRecentEventTime2);
   }
}

EventQueue::QueueItem::QueueItem(RAWSEvent e)
   :evnt(e)
{
   id = 0;
}

} /* namespace aws */

} /* namespace aro */
