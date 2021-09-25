#ifndef AWSE_FOCUSCAUSEDEVENT_H
#define AWSE_FOCUSCAUSEDEVENT_H

#include <aro/aws/event/FocusEvent.h>

namespace aro {

namespace aws {

namespace event {

class FocusCausedEvent;
typedef Ref<FocusCausedEvent> RFocusCausedEvent;

class FocusCausedEvent : public FocusEvent
{
   public:
      class Cause;
      typedef Ref<Cause> RCause;

      virtual RCause getCause();
      
      FocusCausedEvent(RComponent source, vint id,
         vbool temp, RComponent other, RCause cause);
   
   private:
      RCause cause;
};

class FocusCausedEvent::Cause : public Object
{
   public:
      static const RCause MOUSE;
      static const RCause MANUAL;
      static const RCause UNKNOWN;
      static const RCause ROLLBACK;
      static const RCause AUTOMATIC;
      static const RCause ACTIVATION;
      static const RCause RETARGETED;
      static const RCause FOCUSING;
      static const RCause FOCUS_NEXT;
      static const RCause FOCUS_PREVIOUS;
      static const RCause NATIVE_SYSTEM;
      static const RCause CLEAR_FOCUS_OWNER;
   
   private:
      Cause() = default;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_FOCUSCAUSEDEVENT_H */
