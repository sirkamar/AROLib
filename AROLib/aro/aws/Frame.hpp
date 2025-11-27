#ifndef AWS_FRAME_H
#define AWS_FRAME_H

#include <aro/aws/Window.hpp>

namespace aro {

namespace aws {

class Frame;
typedef Ref<Frame> RFrame;

class Frame extends public Window
{
   public:
      Frame();
      Frame(RString title);
      Frame(RWindow owner);
      Frame(RWindow owner, RString title);
      
      virtual void setTitle(RString title);
      virtual RString getTitle();
      
      virtual RInsets getInsets();
      virtual void paint(RGraphics g);
   
   protected:
      RString title;

      virtual void postProcessKeyEvent(event::RKeyEvent e);

};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_FRAME_H */
