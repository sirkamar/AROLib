#include <aro/core.h>
#include <aro/aws/Component.h>
#include <aro/aws/event/InputEvent.h>

namespace aro {

namespace aws {

namespace event {

InputEvent::InputEvent(RComponent source, vint id, vlong w, vint mod)
   :ComponentEvent(source, id)
{
   when = w;
   modifiers = mod;
}

vint InputEvent::getModifiers()
{
   return modifiers;
}

vlong InputEvent::getWhen()
{
   return when;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
