#ifndef AWSE_COMPONENTLISTENER_H
#define AWSE_COMPONENTLISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class ComponentEvent;
interface ComponentListener;
typedef Ref<ComponentEvent> RComponentEvent;
typedef Ref<ComponentListener> RComponentListener;

interface ComponentListener extends util::Listener
{
   public:
      virtual void componentMoved(RComponentEvent e)=0;
      virtual void componentShown(RComponentEvent e)=0;
      virtual void componentHidden(RComponentEvent e)=0;
      virtual void componentResized(RComponentEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* NAMESPACE aro */

#endif /* AWSE_COMPONENTLISTENER_H */
