#ifndef AWS_KEYEVENT_H
#define AWS_KEYEVENT_H

#include <aro/aws/event/InputEvent.hpp>

namespace aro {

namespace aws {

namespace event {

class KeyEvent;
typedef Ref<KeyEvent> RKeyEvent;

class KeyEvent extends public InputEvent
{
   public:
      /* KeyEvent constansts */
      static const vint KEY_TYPED         = 1001011;
      static const vint KEY_PRESSED       = 1001012;
      static const vint KEY_RELEASED      = 1001013;
      
      /* Modifier Key bit masks */
      static const vint SHIFT_MASK;
      static const vint ALT_MASK;
      static const vint CTRL_MASK;
      static const vint META_MASK;
      static const vint ALT_GRAPH_MASK;
      
      /* Virtual Key codes */
      static const vint VKEY_ENTER;
      static const vint VKEY_BACKSPACE;
      static const vint VKEY_TAB;
      static const vint VKEY_CANCEL;
      static const vint VKEY_CLEAR;
      static const vint VKEY_SHIFT;
      static const vint VKEY_CONTROL;
      static const vint VKEY_ALT;
      static const vint VKEY_PAUSE;
      static const vint VKEY_CAPS_LOCK;
      static const vint VKEY_ESCAPE;
      static const vint VKEY_SPACE;
      static const vint VKEY_PAGE_UP;
      static const vint VKEY_PAGE_DOWN;
      static const vint VKEY_END;
      static const vint VKEY_HOME;
      
      static const vint VKEY_LEFT;
      static const vint VKEY_UP;
      static const vint VKEY_RIGHT;
      static const vint VKEY_DOWN;
      
      static const vint VKEY_COMMA;
      static const vint VKEY_MINUS;
      static const vint VKEY_PERIOD;
      static const vint VKEY_SLASH;
      
      static const vint VKEY_0;
      static const vint VKEY_1;
      static const vint VKEY_2;
      static const vint VKEY_3;
      static const vint VKEY_4;
      static const vint VKEY_5;
      static const vint VKEY_6;
      static const vint VKEY_7;
      static const vint VKEY_8;
      static const vint VKEY_9;
      
      static const vint VKEY_SEMICOLON;
      static const vint VKEY_EQUALS;
      
      static const vint VKEY_A;
      static const vint VKEY_B;
      static const vint VKEY_C;
      static const vint VKEY_D;
      static const vint VKEY_E;
      static const vint VKEY_F;
      static const vint VKEY_G;
      static const vint VKEY_H;
      static const vint VKEY_I;
      static const vint VKEY_J;
      static const vint VKEY_K;
      static const vint VKEY_L;
      static const vint VKEY_M;
      static const vint VKEY_N;
      static const vint VKEY_O;
      static const vint VKEY_P;
      static const vint VKEY_Q;
      static const vint VKEY_R;
      static const vint VKEY_S;
      static const vint VKEY_T;
      static const vint VKEY_U;
      static const vint VKEY_V;
      static const vint VKEY_W;
      static const vint VKEY_X;
      static const vint VKEY_Y;
      static const vint VKEY_Z;
      
      static const vint VKEY_OPEN_BRACKET;
      static const vint VKEY_BACK_SLASH;
      static const vint VKEY_CLOSE_BRACKET;
      
      static const vint VKEY_NUMPAD0;
      static const vint VKEY_NUMPAD1;
      static const vint VKEY_NUMPAD2;
      static const vint VKEY_NUMPAD3;
      static const vint VKEY_NUMPAD4;
      static const vint VKEY_NUMPAD5;
      static const vint VKEY_NUMPAD6;
      static const vint VKEY_NUMPAD7;
      static const vint VKEY_NUMPAD8;
      static const vint VKEY_NUMPAD9;
      static const vint VKEY_MULTIPLY;
      static const vint VKEY_ADD;
      
      static const vint VKEY_SEPARATOR;
      
      static const vint VKEY_SUBTRACT;
      static const vint VKEY_DECIMAL;
      static const vint VKEY_DIVIDE;
      static const vint VKEY_DELETE;
      static const vint VKEY_NUM_LOCK;
      static const vint VKEY_SCROLL_LOCK;
      
      static const vint VKEY_F1;
      static const vint VKEY_F2;
      static const vint VKEY_F3;
      static const vint VKEY_F4;
      static const vint VKEY_F5;
      static const vint VKEY_F6;
      static const vint VKEY_F7;
      static const vint VKEY_F8;
      static const vint VKEY_F9;
      static const vint VKEY_F10;
      static const vint VKEY_F11;
      static const vint VKEY_F12;
      
      static const vint VKEY_PRINTSCREEN;
      static const vint VKEY_INSERT;
      static const vint VKEY_HELP;
      static const vint VKEY_META;
      
      static const vint VKEY_BACKQUOTE;
      static const vint VKEY_QUOTE;
      
      static const vint VKEY_KP_UP;
      static const vint VKEY_KP_DOWN;
      static const vint VKEY_KP_LEFT;
      static const vint VKEY_KP_RIGHT;
      
      static const vint VKEY_AMPERSAND;
      static const vint VKEY_ASTERISK;
      static const vint VKEY_QUOTEDBL;
      static const vint VKEY_LESS;
      static const vint VKEY_GREATER;
      static const vint VKEY_BRACE_LEFT;
      static const vint VKEY_BRACE_RIGHT;
      
      static const vint VKEY_AT;
      static const vint VKEY_COLON;
      static const vint VKEY_CIRCUMFLEX;
      static const vint VKEY_DOLLAR;
      
      static const vint VKEY_EXCLAMATION;
      static const vint VKEY_LEFT_PARENTHESIS;
      static const vint VKEY_NUMBER_SIGN;
      static const vint VKEY_PLUS;
      static const vint VKEY_RIGHT_PARENTHESIS;
      static const vint VKEY_UNDERSCORE;
      
      static const vint VKEY_WINDOWS;
      static const vint VKEY_CONTEXT_MENU;
      
      static const vint VKEY_COMPOSE;
      static const vint VKEY_ALT_GRAPH;
      static const vint VKEY_BEGIN;
      
      /* Unknown Key or KEY_TYPED events */
      static const vint VKEY_UNDEFINED;
      
      /* KEY_PRESSED and KEY_RELEASED events */
      static const vint CHAR_UNDEFINED;
      
      /* KEY_TYPED events */
      static const vint KEY_LOCATION_UNKNOWN;
      
      /* Key Location constants */
      static const vint KEY_LOCATION_STANDARD;
      static const vint KEY_LOCATION_LEFT;
      static const vint KEY_LOCATION_RIGHT;
      static const vint KEY_LOCATION_NUMPAD;
      
      virtual vbool isAltDown();
      virtual vbool isMetaDown();
      virtual vbool isShiftDown();
      virtual vbool isActionKey();
      virtual vbool isControlDown();
      virtual vbool isAltGraphDown();
      
      virtual vint getKeyCode();
      virtual vchar getKeyChar();
      virtual vint getKeyLocation();

      static RString getKeyText(vint keyCode);
      static RString getKeyModifiersText(vint modifiers);
      
      KeyEvent(RComponent src,vint id,vlong when,vint modifiers,vint keyCode,vchar keyChar);
      KeyEvent(RComponent src,vint id,vlong when,vint modifiers,vint keyCode,vchar keyChar,vint keyLocation);
   
   protected:
      vint keyCode;
      vchar keyChar;
      vint keyLocation;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_KEYEVENT_H */
