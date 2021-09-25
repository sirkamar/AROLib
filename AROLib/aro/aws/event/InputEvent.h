#ifndef AWSE_INPUTEVENT_H
#define AWSE_INPUTEVENT_H

#include <aro/aws/event/ComponentEvent.h>

namespace aro {

namespace aws {

namespace event {

class InputEvent;
typedef Ref<InputEvent> RInputEvent;

class InputEvent : public ComponentEvent
{
   public:
      InputEvent(RComponent source, vint id, vlong when, vint modifiers);
      
      virtual vint getModifiers();
      
      virtual vlong getWhen();

   protected:
      vlong when;
      vint modifiers;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_INPUTEVENT_H */
