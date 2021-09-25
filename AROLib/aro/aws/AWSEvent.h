#ifndef AWS_AWSEVENT_H
#define AWS_AWSEVENT_H

#include <aro/util/Event.h>

namespace aro {

namespace aws {

class AWSEvent;
typedef Ref<AWSEvent> RAWSEvent;

class AWSEvent : public util::Event
{
   public:
      AWSEvent(RObject source, vint eventID);
      
      vbool isConsumed();
      vint getEventID();
      void consume();
   
   protected:
      vint eventID;
      vbool consumed;
      vbool isPosted;
      vbool dispatched;
      
      static vint getNewID();
   
   private:
      static vint count;
      vbool atFocusManager;
   
   friend class Component;
   friend class EventQueue;
   friend class FocusManager;
   friend class DefaultFocusManager;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_AWSEVENT_H */
