#include <aro/core.hpp>
#include <aro/aws/Component.hpp>
#include <aro/aws/event/ItemEvent.hpp>
#include <aro/aws/Selectable.hpp>


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

