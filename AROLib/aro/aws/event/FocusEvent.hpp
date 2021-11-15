#ifndef AWSE_FOCUSEVENT_H
#define AWSE_FOCUSEVENT_H

#include <aro/aws/event/ComponentEvent.hpp>

namespace aro {

namespace aws {

namespace event {

class FocusEvent;
typedef Ref<FocusEvent> RFocusEvent;

class FocusEvent : public ComponentEvent
{
   public:
      static const vint GOT_FOCUS   = 1001006;
      static const vint LOST_FOCUS  = 1001007;
      
      FocusEvent(RComponent source, vint id);
      FocusEvent(RComponent source, vint id, vbool temp);
      FocusEvent(RComponent source, vint id, vbool temp, RComponent other);
      
      virtual RComponent getOtherComponent();
      virtual vbool isTemporary();
   
   private:
      vbool temporary;
      RComponent other;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_FOCUSEVENT_H */
