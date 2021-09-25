#ifndef AWSE_WINDOWEVENT_H
#define AWSE_WINDOWEVENT_H

#include <aro/aws/AWSEvent.h>
#include <aro/aws/Window.h>

namespace aro {

namespace aws {

namespace event {

class WindowEvent;
typedef Ref<WindowEvent> RWindowEvent;

class WindowEvent : public AWSEvent
{
   public:
      static const vint WINDOW_OPENED        = 1001020;
      static const vint WINDOW_CLOSED        = 1001021;
      static const vint WINDOW_CLOSING       = 1001022;
      static const vint WINDOW_ACTIVATED     = 1001023;
      static const vint WINDOW_GOT_FOCUS     = 1001024;
      static const vint WINDOW_LOST_FOCUS    = 1001025;
      static const vint WINDOW_DEACTIVATED   = 1001026;
      
      WindowEvent(RWindow source, vint id, RWindow other);
      WindowEvent(RWindow source, vint id);
      virtual RWindow getOtherWindow();
      virtual RWindow getWindow();
   
   private:
      RWindow other;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_WINDOWEVENT_H */
