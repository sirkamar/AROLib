#include <aro/core.hpp>
#include <aro/aws/Component.hpp>
#include <aro/aws/event/InputEvent.hpp>

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
