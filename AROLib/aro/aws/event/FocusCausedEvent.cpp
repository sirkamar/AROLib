#include <aro/core.h>
#include <aro/aws/Component.h>
#include <aro/aws/event/FocusCausedEvent.h>

namespace aro {

namespace aws {

namespace event {

FocusCausedEvent::FocusCausedEvent(RComponent source, vint id,
     vbool temp, RComponent other, FocusCausedEvent::RCause cause)
   :FocusEvent(source, id, temp, other), cause(cause)
{
   //thisref->cause = cause;
}

FocusCausedEvent::RCause FocusCausedEvent::getCause()
{
   return cause;
}

const FocusCausedEvent::RCause FocusCausedEvent::Cause::MOUSE = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::MANUAL = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::UNKNOWN = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::ROLLBACK = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::AUTOMATIC = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::ACTIVATION = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::RETARGETED = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::FOCUSING = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::FOCUS_NEXT = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::FOCUS_PREVIOUS = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::NATIVE_SYSTEM = new FocusCausedEvent::Cause();

const FocusCausedEvent::RCause FocusCausedEvent::Cause::CLEAR_FOCUS_OWNER = new FocusCausedEvent::Cause();

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
