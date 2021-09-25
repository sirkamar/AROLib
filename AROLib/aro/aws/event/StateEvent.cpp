#include <aro/core.h>
#include <aro/aws/Selectable.h>
#include <aro/aws/event/StateEvent.h>

namespace aro {

namespace aws {

namespace event {

const vint StateEvent::SELECTED = 1;

const vint StateEvent::DESELECTED = 2;

//const vint StateEvent::STATE_CHANGED = getNewID();

StateEvent::StateEvent(RSelectable src, vint id, RObject itm, vint cng)
   :AWSEvent(src, id)
{
   item = itm;
   stateChange = cng;
}

RSelectable StateEvent::getSelectable()
{
   return type_cast<Selectable>(source);
}

vint StateEvent::getStateChange()
{
   return stateChange;
}

RObject StateEvent::getItem()
{
   return item;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
