#ifndef AWSE_PROPERTYLISTENER_H
#define AWSE_PROPERTYLISTENER_H

#include <aro/util/Listener.h>
//#include <aro/aws/event/PropertyEvent.h>

namespace aro {

namespace aws {

namespace event {

class PropertyEvent;
interface PropertyListener;
typedef Ref<PropertyEvent> RPropertyEvent;
typedef Ref<PropertyListener> RPropertyListener;

interface PropertyListener : util::Listener
{
   virtual void propertyChanged(RPropertyEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_PROPERTYLISTENER_H */
