#include <aro/core.h>
#include <aro/aws/event/ActionEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint ActionEvent::ACTION_OCCURRED = getNewID();

ActionEvent::ActionEvent(RObject src, vint id, RString cmd, vlong w, vint mod)
   :AWSEvent(src, id)
{
   modifiers = mod;
   command = cmd;
   when = w;
}

ActionEvent::ActionEvent(RObject src, vint id, RString cmd, vint mod)
   :AWSEvent(src, id)
{
   modifiers = mod;
   command = cmd;
   when = 0;
}

ActionEvent::ActionEvent(RObject src, vint id, RString cmd)
   :AWSEvent(src, id)
{
   modifiers = 0;
   command = cmd;
   when = 0;
}

RString ActionEvent::getCommand()
{
   return command;
}

vint ActionEvent::getModifiers()
{
   return modifiers;
}

vlong ActionEvent::getWhen()
{
   return when;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
