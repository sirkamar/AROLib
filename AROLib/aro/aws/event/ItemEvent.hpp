#ifndef AWS_ITEMEVENT_H
#define AWS_ITEMEVENT_H

#include <aro/aws/AWSEvent.hpp>

namespace aro {

namespace aws {

interface Selectable;
typedef Ref<Selectable> RSelectable;

namespace event {

class ItemEvent;
typedef Ref<ItemEvent> RItemEvent;

class ItemEvent extends public AWSEvent
{
   public:
      static const vint SELECTED              = 1001008;
      static const vint DESELECTED            = 1001009;
      static const vint ITEM_STATE_CHANGED    = 1001010;
      
      ItemEvent(RSelectable source, vint id, RObject item, vint change);
      virtual RSelectable getSelectable();
      virtual vint getStateChange();
      virtual RObject getItem();
   
   private:
      int stateChange;
      RObject item;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_ITEMEVENT_H */
