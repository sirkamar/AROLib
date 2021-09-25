#ifndef AWS_KEYSTROKE_H
#define AWS_KEYSTROKE_H

#include <aro/core/String.h>
#include <aro/util/List.h>

namespace aro {

class Char;
typedef Ref<Char> RChar;

namespace aws {

namespace event {

class KeyEvent;
typedef Ref<KeyEvent> RKeyEvent;

}

class KeyStroke;
typedef Ref<KeyStroke> RKeyStroke;

class KeyStroke : public Object
{
   public:
      static RKeyStroke getKeyStroke(vchar keyChar);
      static RKeyStroke getKeyStroke(vint keyCode, vint modifiers);
      static RKeyStroke getKeyStroke(RChar keyChar, vint modifiers);
      static RKeyStroke getKeyStroke(vint keyCode, vint modifiers, vbool onRelease);
      static RKeyStroke getKeyStroke(vchar keyChar, vint keyCode, vint modifiers, vbool onRelease);
      
      static RKeyStroke getKeyStrokeForEvent(event::RKeyEvent e);
      
      virtual vbool equals(RObject obj);
      
      vint getKeyEventType();
      vbool isOnRelease();
      vint getModifiers();
      vchar getKeyChar();
      vint getKeyCode();
   
   protected:
      KeyStroke();
      KeyStroke(vchar keyChar, vint keyCode, vint modifiers, vbool onRelease);
   
   private:
      vint keyCode;
      vchar keyChar;
      vint modifiers;
      vbool onRelease;
      
      static RKeyStroke cacheKey;
      static util::RList<KeyStroke> cache;
      
      static RKeyStroke getCachedKeyStroke(vchar keyChar, vint keyCode,
                                           vint modifiers, vbool onRelease);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_KEYSTROKE_H */
