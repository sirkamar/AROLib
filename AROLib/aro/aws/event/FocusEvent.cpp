#include <aro/core.h>
#include <aro/aws/Component.h>
#include <aro/aws/event/FocusEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint FocusEvent::GOT_FOCUS = getNewID();
//
//const vint FocusEvent::LOST_FOCUS = getNewID();

FocusEvent::FocusEvent(RComponent src, vint id, vbool temp, RComponent otr)
   :ComponentEvent(src, id)
{
   temporary = temp;
   other = otr;
}

FocusEvent::FocusEvent(RComponent src, vint id, vbool temp)
   :ComponentEvent(src, id)
{
   temporary = temp;
   other = nullref;
}

FocusEvent::FocusEvent(RComponent src, vint id)
   :ComponentEvent(src, id)
{
   temporary = false;
   other = nullref;
}

RComponent FocusEvent::getOtherComponent()
{
   return other;
}

vbool FocusEvent::isTemporary()
{
   return temporary;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
