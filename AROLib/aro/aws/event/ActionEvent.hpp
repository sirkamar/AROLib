#ifndef AWSE_ACTIONEVENT_H
#define AWSE_ACTIONEVENT_H

#include <aro/aws/AWSEvent.hpp>

namespace aro {

namespace aws {

namespace event {

class ActionEvent;
typedef Ref<ActionEvent> RActionEvent;

class ActionEvent : public AWSEvent
{
   public:
      static const vint ACTION_OCCURRED = 1001001;
      
      ActionEvent(RObject source, vint id, RString command, vlong when, vint modifiers);

      ActionEvent(RObject source, vint id, RString command, vint modifiers);

      ActionEvent(RObject source, vint id, RString command);
      
      virtual RString getCommand();

      virtual vint getModifiers();

      virtual vlong getWhen();
   
   protected:
      RString command;
      vint modifiers;
      vlong when;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_ACTIONEVENT_H */
