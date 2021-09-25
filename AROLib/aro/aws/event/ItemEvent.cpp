#include <aro/core.h>
#include <aro/aws/Component.h>
#include <aro/aws/event/ItemEvent.h>
#include <aro/aws/Selectable.h>


namespace aro {

namespace aws {

namespace event {

ItemEvent::ItemEvent(RSelectable source, vint id, RObject item, vint change)
   :AWSEvent(source, id)
{
   thisref->item = item;
   stateChange = change;
}

RSelectable ItemEvent::getSelectable()
{
   return type_cast<Selectable>(source);
}

vint ItemEvent::getStateChange()
{
   return stateChange;
}

RObject ItemEvent::getItem()
{
   return item;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

