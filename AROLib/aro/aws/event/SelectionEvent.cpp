#include <aro/core.h>
#include <aro/aws/event/SelectionEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint SelectionEvent::VALUE_CHANGED = getNewID();

SelectionEvent::SelectionEvent(RObject src, vint first, vint last)
   :AWSEvent(src, VALUE_CHANGED)
{
   firstIndex = first;
   lastIndex = last;
}

vint SelectionEvent::getFirstIndex()
{
   return firstIndex;
}

vint SelectionEvent::getLastIndex()
{
   return lastIndex;
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
