#ifndef AWSE_KEYADAPTER_H
#define AWSE_KEYADAPTER_H

#include <aro/aws/event/KeyListener.h>

namespace aro {

namespace aws {

namespace event {

class KeyAdapter;
typedef Ref<KeyAdapter> RKeyAdpter;

class KeyAdapter : public Object, public KeyListener
{
   public:
      virtual void keyTyped(RKeyEvent e);
      virtual void keyPressed(RKeyEvent e);
      virtual void keyReleased(RKeyEvent e);
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_KEYADAPTER_H */
