#ifndef AWSE_WINDOWLISTENER_H
#define AWSE_WINDOWLISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class WindowEvent;
interface WindowListener;
typedef Ref<WindowEvent> RWindowEvent;
typedef Ref<WindowListener> RWindowListener;

interface WindowListener extends util::Listener
{
   virtual void windowOpened(RWindowEvent e)=0;
   virtual void windowClosed(RWindowEvent e)=0;
   virtual void windowClosing(RWindowEvent e)=0;
   virtual void windowActivated(RWindowEvent e)=0;
   virtual void windowDeactivated(RWindowEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_WINDOWLISTENER_H */
