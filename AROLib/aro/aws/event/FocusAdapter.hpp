#ifndef AWSE_FOCUSADAPTER_H
#define AWSE_FOCUSADAPTER_H

#include <aro/aws/event/FocusListener.hpp>

namespace aro {

namespace aws {

namespace event {

class FocusAdapter;
typedef Ref<FocusAdapter> RFocusAdapter;

class FocusAdapter extends public Object implements public FocusListener
{
   public:
      virtual void gotFocus(RFocusEvent e);
      virtual void lostFocus(RFocusEvent e);
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_FOCUSADAPTER_H */
