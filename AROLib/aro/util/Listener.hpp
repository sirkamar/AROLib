#ifndef AWS_LISTENER_H
#define AWS_LISTENER_H

#include <aro/core/Interface.hpp>

namespace aro {

namespace util {

interface Listener;
typedef Ref<Listener> RListener;

/** The Listener interface is merely used
 * to identify an interface as an event
 * listener interface type. */
interface Listener : Interface
{
   
};

} /* namespace util */

} /* namespace aro */

#endif /* AWS_LISTENER_H */
