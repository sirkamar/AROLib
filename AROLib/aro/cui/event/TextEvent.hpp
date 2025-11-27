#ifndef AWSE_TEXTEVENT_H
#define AWSE_TEXTEVENT_H

#include <aro/aws/AWSEvent.hpp>

namespace aro {

namespace cui {

namespace event {

class TextEvent;
typedef Ref<TextEvent> RTextEvent;

class TextEvent extends public aws::AWSEvent
{
   public:
      static const vint TEXT_CHANGED      = 1001019;
      
      TextEvent(RObject source);
};

} /* namespace event */

} /* namespace cui */

} /* namespace aro */

#endif /* AWSE_TEXTEVENT_H */
