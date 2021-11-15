#ifndef AWS_EVENTDISPATCHER_H
#define AWS_EVENTDISPATCHER_H

#include <aro/core/Thread.hpp>

namespace aro {

namespace aws {

class EventQueue;
class EventDispatcher;
typedef Ref<EventQueue> REventQueue;
typedef Ref<EventDispatcher> REventDispatcher;

class EventDispatcher : public Thread
{
   public:
      virtual void run();
   
   private:
      vbool doDispatch;
      
      REventQueue theQueue;
      
      EventDispatcher(RString name, REventQueue queue);
   
   friend class EventQueue;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_EVENTDISPATCHER_H */
