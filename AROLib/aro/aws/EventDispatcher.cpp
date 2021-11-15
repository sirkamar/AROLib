#include <aro/core.hpp>
#include <aro/aws/EventQueue.hpp>
#include <aro/aws/EventDispatcher.hpp>

namespace aro {

namespace aws {

EventDispatcher::EventDispatcher(RString name, REventQueue queue)
   :Thread(name)
{
   theQueue = queue;

   doDispatch = true;
}

void EventDispatcher::run()
{
   ex_try
   {
      /*
      * In effect, this is a while(true) condition.
      * It might be wise to devise a means of being
      * able to setting doDispatch to false, however,
      * outside of an exception (which will exit the
      * the loop anyway) that isn't really necessary.
      * May be post a ShutdownEvent to indicate exit.
      */
      while(doDispatch)
      {
         RAWSEvent e = theQueue->getNextEvent();
         
         if(e == nullref)
            doDispatch = false;
         else
            theQueue->dispatchEvent(e);
      }

      ex_throw new __FinalEx__(); // cause detach
   }
   ex_catch
   {
      ex_finally
      {
         /*
         * This synchronized block is to secure that the
         * event dispatch thread won't die in the middle
         * of posting a new event to the associated
         * event queue. The EventQueue::dispatcher
         * must be a valid (non-null) reference.
         */
         sync_lock(theQueue)
         {
            if(theQueue->getDispatcher() == thisref)
               theQueue->detachDispatcher();

            /*
            * Event dispatch thread dies in case of an uncaught exception.
            * A new event dispatch thread for this queue will be started
            * only if a new event is posted to it. In case if no more
            * events are posted after this thread died all events that
            * currently are in the queue will never be dispatched.
            */
            RAWSEvent e = theQueue->peekEvent();
            if(e != nullref)
               theQueue->initDispatcher();
         }
      }
   }
   ex_end
}

} /* namespace aws */

} /* namespace aro */
