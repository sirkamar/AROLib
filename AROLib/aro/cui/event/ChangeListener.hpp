#ifndef CUI_EVENT_CHANGELISTENER_H
#define CUI_EVENT_CHANGELISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace cui {

namespace event {

class ChangeEvent;
interface ChangeListener;
typedef Ref<ChangeEvent> RChangeEvent;
typedef Ref<ChangeListener> RChangeListener;

interface ChangeListener : util::Listener
{
   virtual void stateChanged(RChangeEvent e)=0;
};

} /* namespace event */

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_EVENT_CHANGELISTENER_H */
