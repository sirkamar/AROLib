#ifndef AWSE_KEYLISTENER_H
#define AWSE_KEYLISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class KeyEvent;
interface KeyListener;
typedef Ref<KeyEvent> RKeyEvent;
typedef Ref<KeyListener> RKeyListener;

interface KeyListener : util::Listener
{
   virtual void keyTyped(RKeyEvent e)=0;
   virtual void keyPressed(RKeyEvent e)=0;
   virtual void keyRealeased(RKeyEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_KEYLISTENER_H */
