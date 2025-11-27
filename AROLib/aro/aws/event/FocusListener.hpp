#ifndef AWSE_FOCUSLISTNER_H
#define AWSE_FOCUSLISTNER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class FocusEvent;
interface FocusListener;
typedef Ref<FocusEvent> RFocusEvent;
typedef Ref<FocusListener> RFocusListener;

interface FocusListener extends util::Listener
{
   virtual void gotFocus(RFocusEvent e)=0;
   virtual void lostFocus(RFocusEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_FOCUSLISTNER_H */
