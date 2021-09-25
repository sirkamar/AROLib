#ifndef AWSE_SELECTIONEVENT_H
#define AWSE_SELECTIONEVENT_H

#include <aro/aws/AWSEvent.h>

namespace aro {

namespace aws {

namespace event {

class SelectionEvent;
typedef Ref<SelectionEvent> RSelectionEvent;

class SelectionEvent : public AWSEvent
{
   public:
      static const vint VALUE_CHANGED     = 1001017;
      
      SelectionEvent(RObject source, vint firstIndex, vint lastIndex);
      virtual vint getFirstIndex();
      virtual vint getLastIndex();
   
   private:
      vint firstIndex, lastIndex;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_SELECTIONEVENT_H */
