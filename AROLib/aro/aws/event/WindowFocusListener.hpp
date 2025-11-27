#ifndef AWSE_WINDOWFOCUSLISTENER_H
#define AWSE_WINDOWFOCUSLISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class WindowEvent;
interface WindowFocusListener;
typedef Ref<WindowEvent> RWindowEvent;
typedef Ref<WindowFocusListener> RWindowFocusListener;

interface WindowFocusListener extends util::Listener
{
   virtual void windowGotFocus(RWindowEvent e)=0;
   virtual void windowLostFocus(RWindowEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_WINDOWFOCUSLISTENER_H */
