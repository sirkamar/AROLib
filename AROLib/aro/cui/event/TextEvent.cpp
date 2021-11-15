#include <aro/core.hpp>
#include <aro/cui/event/TextEvent.hpp>

namespace aro {

namespace cui {

namespace event {

//const vint TextEvent::TEXT_CHANGED = getNewID();

TextEvent::TextEvent(RObject src)
   :AWSEvent(src, TEXT_CHANGED)
{
   
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
