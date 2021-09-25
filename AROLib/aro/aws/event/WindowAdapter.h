#ifndef AWSE_WINDOWADAPTER_H
#define AWSE_WINDOWADAPTER_H

#include <aro/aws/event/WindowListener.h>
#include <aro/aws/event/WindowFocusListener.h>

namespace aro {

namespace aws {

namespace event {

class WindowAdapter;
typedef Ref<WindowAdapter> RWindowAdapter;

class WindowAdapter : public Object, public WindowListener, public WindowFocusListener
{
   public:
      virtual void windowOpened(RWindowEvent e);
      virtual void windowClosed(RWindowEvent e);
      virtual void windowClosing(RWindowEvent e);
      virtual void windowGotFocus(RWindowEvent e);
      virtual void windowLostFocus(RWindowEvent e);
      virtual void windowActivated(RWindowEvent e);
      virtual void windowDeactivated(RWindowEvent e);
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_WINDOWADAPTER_H */
