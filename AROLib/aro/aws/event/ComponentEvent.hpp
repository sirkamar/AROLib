#ifndef AWSE_COMPONENTEVENT_H
#define AWSE_COMPONENTEVENT_H

#include <aro/aws/AWSEvent.hpp>

namespace aro {

namespace aws {

class Component;
typedef Ref<Component> RComponent;

namespace event {

class ComponentEvent;
typedef Ref<ComponentEvent> RComponentEvent;

class ComponentEvent : public AWSEvent
{
   public:
      static const vint COMPONENT_MOVED   = 1001002;
      static const vint COMPONENT_SHOWN   = 1001003;
      static const vint COMPONENT_HIDDEN  = 1001004;
      static const vint COMPONENT_RESIZED = 1001005;
      
      ComponentEvent(RComponent source, vint id);
      virtual RComponent getComponent();
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_COMPONENTEVENT_H */
