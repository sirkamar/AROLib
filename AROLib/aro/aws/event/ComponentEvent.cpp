#include <aro/core.h>
#include <aro/aws/Component.h>
#include <aro/aws/event/ComponentEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint ComponentEvent::COMPONENT_RESIZED = getNewID();
//const vint ComponentEvent::COMPONENT_HIDDEN = getNewID();
//const vint ComponentEvent::COMPONENT_SHOWN = getNewID();
//const vint ComponentEvent::COMPONENT_MOVED = getNewID();

ComponentEvent::ComponentEvent(RComponent src, vint id)
   :AWSEvent(src, id)
{
   
}

RComponent ComponentEvent::getComponent()
{
   if(type_of<Component>(source))
      return type_cast<Component>(source);
   
   return nullref;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
