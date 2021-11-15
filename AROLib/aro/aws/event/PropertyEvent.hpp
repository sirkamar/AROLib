#ifndef AWSE_PROPERTYEVENT_H
#define AWSE_PROPERTYEVENT_H

#include <aro/aws/AWSEvent.hpp>

namespace aro {

namespace aws {

namespace event {

class PropertyEvent;
typedef Ref<PropertyEvent> RPropertyEvent;

class PropertyEvent : public AWSEvent
{
   public:
      static const vint PROPERTY_CHANGED     = 1001016;
      
      PropertyEvent(RObject source, vint id,
                    RString propertyName, RObject oldValue, RObject newValue);
      
      virtual RString getPropertyName();
      virtual RObject getOldValue();
      virtual RObject getNewValue();
   
   private:
      RObject newValue, oldValue;
      RString propertyName;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_PROPERTYEVENT_H */
