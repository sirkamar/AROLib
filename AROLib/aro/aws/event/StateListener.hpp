#ifndef AWSE_STATELISTNER_H
#define AWSE_STATELISTNER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class StateEvent;
interface StateListener;
typedef Ref<StateEvent> RStateEvent;
typedef Ref<StateListener> RStateListener;

interface StateListener : util::Listener
{
   virtual void stateChanged(RStateEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_STATELISTNER_H */
