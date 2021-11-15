#ifndef UTIL_EVENT_H
#define UTIL_EVENT_H

#include <aro/core/String.hpp>

namespace aro {

namespace util {

class Event;
typedef Ref<Event> REvent;

class Event : public Object
{
   public:
      virtual void setSource(RObject source);
      virtual RObject getSource();
      Event(RObject source);
   
   protected:
      RObject source;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_EVENT_H */
