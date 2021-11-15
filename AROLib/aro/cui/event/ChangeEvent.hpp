#ifndef CUI_EVENT_CHANGEEVENT_H
#define CUI_EVENT_CHANGEEVENT_H

#include <aro/util/Event.hpp>

namespace aro {

namespace cui {

namespace event {

class ChangeEvent;
typedef Ref<ChangeEvent> RChangeEvent;

class ChangeEvent : public util::Event
{
   public:
      ChangeEvent(RObject source);
};

} /* namespace event */

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_EVENT_CHANGEEVENT_H */
