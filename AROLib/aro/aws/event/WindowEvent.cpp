#include <aro/core.h>
#include <aro/aws/Window.h>
#include <aro/aws/event/WindowEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint WindowEvent::WINDOW_OPENED = getNewID();
//
//const vint WindowEvent::WINDOW_CLOSED = getNewID();
//
//const vint WindowEvent::WINDOW_CLOSING = getNewID();
//
//const vint WindowEvent::WINDOW_ACTIVATED = getNewID();
//
//const vint WindowEvent::WINDOW_GOT_FOCUS = getNewID();
//
//const vint WindowEvent::WINDOW_LOST_FOCUS = getNewID();
//
//const vint WindowEvent::WINDOW_DEACTIVATED = getNewID();

WindowEvent::WindowEvent(RWindow src, vint id, RWindow otr)
   :AWSEvent(src, id)
{
   other = otr;
}

WindowEvent::WindowEvent(RWindow src, vint id)
   :AWSEvent(src, id)
{
   
}

RWindow WindowEvent::getOtherWindow()
{
   return other;
}

RWindow WindowEvent::getWindow()
{
   if(type_of<Window>(source))
      return type_cast<Window>(source);
   
   return nullref;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
