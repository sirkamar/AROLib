#include <aro/core.hpp>
#include <aro/aws/ListenerList.hpp>

namespace aro {

namespace aws {

using namespace util;

ListenerList::ListenerList()
{
   listeners = new ArrayList<Listener>(0);
}

vint ListenerList::getListenerCount()
{
   return listeners->size();
}

RArray<util::Listener> ListenerList::getListeners()
{
   return listeners->toArray();
}

} /* namespace aws */

} /* namespace aro */
