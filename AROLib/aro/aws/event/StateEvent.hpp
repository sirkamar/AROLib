#ifndef AWS_STATEEVENT_H
#define AWS_STATEEVENT_H

#include <aro/aws/AWSEvent.hpp>

namespace aro {

namespace aws {

interface Selectable;
typedef Ref<Selectable> RSelectable;

namespace event {

class StateEvent;
typedef Ref<StateEvent> RStateEvent;

/** This is akin to the ItemEvent class */
class StateEvent : public AWSEvent
{
   public:
      static const vint STATE_CHANGED = 1001018;
      
      static const vint SELECTED;
      static const vint DESELECTED;
      
      StateEvent(RSelectable source, vint id, RObject item, vint change);
      virtual RSelectable getSelectable();
      virtual vint getStateChange();
      virtual RObject getItem();
   
   private:
      vint stateChange;
      RObject item;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_STATEEVENT_H */
