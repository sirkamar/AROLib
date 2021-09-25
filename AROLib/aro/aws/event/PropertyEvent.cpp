#include <aro/core.h>
#include <aro/aws/event/PropertyEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint PropertyEvent::PROPERTY_CHANGED = getNewID();

PropertyEvent::PropertyEvent(RObject src, vint id,
                             RString name, RObject oVal, RObject nVal)
   :AWSEvent(src, id)
{
   propertyName = name;
   oldValue = oVal;
   newValue = nVal;
}

RString PropertyEvent::getPropertyName()
{
   return propertyName;
}

RObject PropertyEvent::getOldValue()
{
   return oldValue;
}

RObject PropertyEvent::getNewValue()
{
   return newValue;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
