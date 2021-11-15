#include <aro/core.hpp>
#include <aro/aws/AWSEvent.hpp>
#include <aro/aws/event/KeyEvent.hpp>

namespace aro {

namespace aws {

using event::KeyEvent;

AWSEvent::AWSEvent(RObject src, vint id)
   :Event(src)
{
   eventID = id;
   consumed = false;
   atFocusManager = false;
}

vint AWSEvent::getEventID()
{
   return eventID;
}

vbool AWSEvent::isConsumed()
{
   return consumed;
}

void AWSEvent::consume()
{
   if(eventID == KeyEvent::KEY_PRESSED || eventID == KeyEvent::KEY_RELEASED)
   {
      consumed = true;
   }
   /*switch(eventID)
   {
      case KeyEvent::KEY_PRESSED:
      case KeyEvent::KEY_RELEASED:
         consumed = true;
         break;
      
      default:
         break;
   }*/
}

vint AWSEvent::getNewID()
{
   return count++;
}

vint AWSEvent::count = 1;

} /* namespace aws */

} /* namespace aro */
