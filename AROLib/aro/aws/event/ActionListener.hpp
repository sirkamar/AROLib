#ifndef AWSE_ACTIONLISTENER_H
#define AWSE_ACTIONLISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class ActionEvent;
interface ActionListener;
typedef Ref<ActionEvent> RActionEvent;
typedef Ref<ActionListener> RActionListener;

interface ActionListener extends util::Listener
{
   virtual void actionOccurred(RActionEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_ACTIONLISTENER_H */
