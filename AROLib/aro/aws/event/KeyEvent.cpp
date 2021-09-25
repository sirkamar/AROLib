#include <aro/core.h>
#include <aro/aws/Component.h>
#include <aro/core/ArgumentException.h>
#include <aro/core/StringBuffer.h>
#include <aro/aws/event/KeyEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint KeyEvent::KEY_TYPED    = getNewID();
//const vint KeyEvent::KEY_PRESSED  = getNewID();
//const vint KeyEvent::KEY_RELEASED = getNewID();

const vint KeyEvent::ALT_MASK        = 1 << 3;
const vint KeyEvent::CTRL_MASK       = 1 << 1;
const vint KeyEvent::META_MASK       = 1 << 2;
const vint KeyEvent::SHIFT_MASK      = 1 << 0;
const vint KeyEvent::ALT_GRAPH_MASK  = 1 << 5;

/* Virtual Key codes */
const vint KeyEvent::VKEY_ENTER           = VK_RETURN;
const vint KeyEvent::VKEY_BACKSPACE       = VK_BACK;
const vint KeyEvent::VKEY_TAB             = VK_TAB;
const vint KeyEvent::VKEY_CANCEL          = VK_CANCEL;
const vint KeyEvent::VKEY_CLEAR           = VK_CLEAR;
const vint KeyEvent::VKEY_SHIFT           = VK_SHIFT;
const vint KeyEvent::VKEY_CONTROL         = VK_CONTROL;
const vint KeyEvent::VKEY_ALT             = VK_MENU;
const vint KeyEvent::VKEY_PAUSE           = VK_PAUSE;
const vint KeyEvent::VKEY_CAPS_LOCK       = VK_CAPITAL;
const vint KeyEvent::VKEY_ESCAPE          = VK_ESCAPE;
const vint KeyEvent::VKEY_SPACE           = VK_SPACE;
const vint KeyEvent::VKEY_PAGE_UP         = VK_PRIOR;
const vint KeyEvent::VKEY_PAGE_DOWN       = VK_NEXT;
const vint KeyEvent::VKEY_END             = VK_END;
const vint KeyEvent::VKEY_HOME            = VK_HOME;

const vint KeyEvent::VKEY_LEFT            = VK_LEFT;
const vint KeyEvent::VKEY_UP              = VK_UP;
const vint KeyEvent::VKEY_RIGHT           = VK_RIGHT;
const vint KeyEvent::VKEY_DOWN            = VK_DOWN;

const vint KeyEvent::VKEY_COMMA           = 0x2C;
const vint KeyEvent::VKEY_MINUS           = 0x2D;
const vint KeyEvent::VKEY_PERIOD          = VK_OEM_PERIOD; //0x2E;
const vint KeyEvent::VKEY_SLASH           = 0x2F;

const vint KeyEvent::VKEY_0               = 0x30;
const vint KeyEvent::VKEY_1               = 0x31;
const vint KeyEvent::VKEY_2               = 0x32;
const vint KeyEvent::VKEY_3               = 0x33;
const vint KeyEvent::VKEY_4               = 0x34;
const vint KeyEvent::VKEY_5               = 0x35;
const vint KeyEvent::VKEY_6               = 0x36;
const vint KeyEvent::VKEY_7               = 0x37;
const vint KeyEvent::VKEY_8               = 0x38;
const vint KeyEvent::VKEY_9               = 0x39;

const vint KeyEvent::VKEY_SEMICOLON       = 0x3B;
const vint KeyEvent::VKEY_EQUALS          = 0x3D;

const vint KeyEvent::VKEY_A               = 0x41;
const vint KeyEvent::VKEY_B               = 0x42;
const vint KeyEvent::VKEY_C               = 0x43;
const vint KeyEvent::VKEY_D               = 0x44;
const vint KeyEvent::VKEY_E               = 0x45;
const vint KeyEvent::VKEY_F               = 0x46;
const vint KeyEvent::VKEY_G               = 0x47;
const vint KeyEvent::VKEY_H               = 0x48;
const vint KeyEvent::VKEY_I               = 0x49;
const vint KeyEvent::VKEY_J               = 0x4A;
const vint KeyEvent::VKEY_K               = 0x4B;
const vint KeyEvent::VKEY_L               = 0x4C;
const vint KeyEvent::VKEY_M               = 0x4D;
const vint KeyEvent::VKEY_N               = 0x4E;
const vint KeyEvent::VKEY_O               = 0x4F;
const vint KeyEvent::VKEY_P               = 0x50;
const vint KeyEvent::VKEY_Q               = 0x51;
const vint KeyEvent::VKEY_R               = 0x52;
const vint KeyEvent::VKEY_S               = 0x53;
const vint KeyEvent::VKEY_T               = 0x54;
const vint KeyEvent::VKEY_U               = 0x55;
const vint KeyEvent::VKEY_V               = 0x56;
const vint KeyEvent::VKEY_W               = 0x57;
const vint KeyEvent::VKEY_X               = 0x58;
const vint KeyEvent::VKEY_Y               = 0x59;
const vint KeyEvent::VKEY_Z               = 0x5A;

const vint KeyEvent::VKEY_OPEN_BRACKET    = 0x5B;
const vint KeyEvent::VKEY_BACK_SLASH      = 0x5C;
const vint KeyEvent::VKEY_CLOSE_BRACKET   = 0x5D;

const vint KeyEvent::VKEY_NUMPAD0         = VK_NUMPAD0;
const vint KeyEvent::VKEY_NUMPAD1         = VK_NUMPAD1;
const vint KeyEvent::VKEY_NUMPAD2         = VK_NUMPAD2;
const vint KeyEvent::VKEY_NUMPAD3         = VK_NUMPAD3;
const vint KeyEvent::VKEY_NUMPAD4         = VK_NUMPAD4;
const vint KeyEvent::VKEY_NUMPAD5         = VK_NUMPAD5;
const vint KeyEvent::VKEY_NUMPAD6         = VK_NUMPAD6;
const vint KeyEvent::VKEY_NUMPAD7         = VK_NUMPAD7;
const vint KeyEvent::VKEY_NUMPAD8         = VK_NUMPAD8;
const vint KeyEvent::VKEY_NUMPAD9         = VK_NUMPAD9;
const vint KeyEvent::VKEY_MULTIPLY        = VK_MULTIPLY;
const vint KeyEvent::VKEY_ADD             = VK_ADD;

const vint KeyEvent::VKEY_SEPARATOR       = VK_SEPARATOR;

const vint KeyEvent::VKEY_SUBTRACT        = VK_SUBTRACT;
const vint KeyEvent::VKEY_DECIMAL         = VK_DECIMAL;
const vint KeyEvent::VKEY_DIVIDE          = VK_DIVIDE;
const vint KeyEvent::VKEY_DELETE          = VK_DELETE;
const vint KeyEvent::VKEY_NUM_LOCK        = VK_NUMLOCK;
const vint KeyEvent::VKEY_SCROLL_LOCK     = VK_SCROLL;

const vint KeyEvent::VKEY_F1              = VK_F1;
const vint KeyEvent::VKEY_F2              = VK_F2;
const vint KeyEvent::VKEY_F3              = VK_F3;
const vint KeyEvent::VKEY_F4              = VK_F4;
const vint KeyEvent::VKEY_F5              = VK_F5;
const vint KeyEvent::VKEY_F6              = VK_F6;
const vint KeyEvent::VKEY_F7              = VK_F7;
const vint KeyEvent::VKEY_F8              = VK_F8;
const vint KeyEvent::VKEY_F9              = VK_F9;
const vint KeyEvent::VKEY_F10             = VK_F10;
const vint KeyEvent::VKEY_F11             = VK_F11;
const vint KeyEvent::VKEY_F12             = VK_F12;

const vint KeyEvent::VKEY_PRINTSCREEN     = 0x9A;
const vint KeyEvent::VKEY_INSERT          = 0x9B;
const vint KeyEvent::VKEY_HELP            = 0x9C;
const vint KeyEvent::VKEY_META            = 0x9D;

const vint KeyEvent::VKEY_BACKQUOTE       = 0xC0;
const vint KeyEvent::VKEY_QUOTE           = 0xDE;

const vint KeyEvent::VKEY_KP_UP           = 0xE0;
const vint KeyEvent::VKEY_KP_DOWN         = 0xE1;
const vint KeyEvent::VKEY_KP_LEFT         = 0xE2;
const vint KeyEvent::VKEY_KP_RIGHT        = 0xE3;

const vint KeyEvent::VKEY_AMPERSAND       = 0x96;
const vint KeyEvent::VKEY_ASTERISK        = 0x97;
const vint KeyEvent::VKEY_QUOTEDBL        = 0x98;
const vint KeyEvent::VKEY_LESS            = 0x99;
const vint KeyEvent::VKEY_GREATER         = 0xA0;
const vint KeyEvent::VKEY_BRACE_LEFT      = 0xA1;
const vint KeyEvent::VKEY_BRACE_RIGHT     = 0xA2;

const vint KeyEvent::VKEY_AT              = 0x0200;
const vint KeyEvent::VKEY_COLON           = 0x0201;
const vint KeyEvent::VKEY_CIRCUMFLEX      = 0x0202;
const vint KeyEvent::VKEY_DOLLAR          = 0x0203;

const vint KeyEvent::VKEY_EXCLAMATION        = 0x0205;
const vint KeyEvent::VKEY_LEFT_PARENTHESIS   = 0x0207;
const vint KeyEvent::VKEY_NUMBER_SIGN        = 0x0208;
const vint KeyEvent::VKEY_PLUS               = 0x0209;
const vint KeyEvent::VKEY_RIGHT_PARENTHESIS  = 0x020A;
const vint KeyEvent::VKEY_UNDERSCORE         = 0x020B;

const vint KeyEvent::VKEY_WINDOWS            = 0x020C;
const vint KeyEvent::VKEY_CONTEXT_MENU       = 0x020D;

const vint KeyEvent::VKEY_COMPOSE            = 0xFF20;
const vint KeyEvent::VKEY_ALT_GRAPH          = 0xFF7E;
const vint KeyEvent::VKEY_BEGIN              = 0xFF58;

/* Unknown Key and KEY_TYPED events */
const vint KeyEvent::VKEY_UNDEFINED        = 0x0;

/* KEY_PRESSED and KEY_RELEASED events */
const vint KeyEvent::CHAR_UNDEFINED        = 0xFFFF;

/* KEY_TYPED events */
const vint KeyEvent::KEY_LOCATION_UNKNOWN  = 0;

/* Key Location constants */
const vint KeyEvent::KEY_LOCATION_STANDARD = 1;
const vint KeyEvent::KEY_LOCATION_LEFT     = 2;
const vint KeyEvent::KEY_LOCATION_RIGHT    = 3;
const vint KeyEvent::KEY_LOCATION_NUMPAD   = 4;

KeyEvent::KeyEvent(RComponent src, vint id, vlong w, vint mod, vint kCode, vchar kChar, vint kLoc)
   :InputEvent(src, id, w, mod)
{
   if(id == KEY_TYPED)
   {
      if(kChar == CHAR_UNDEFINED)
         ex_throw new ArgumentException("invalid keyChar");
      
      if(kCode != VKEY_UNDEFINED)
         ex_throw new ArgumentException("invalid keyCode");
      
      if(kLoc != KEY_LOCATION_UNKNOWN)
         ex_throw new ArgumentException("invalid keyLocation");
   }
   
   if(kLoc < KEY_LOCATION_UNKNOWN || kLoc > KEY_LOCATION_NUMPAD)
      ex_throw new ArgumentException("invalid keyLocation");
   
   keyLocation = kLoc;
   keyCode = kCode;
   keyChar = kChar;
}

KeyEvent::KeyEvent(RComponent src, vint id, vlong w, vint mod, vint kCode, vchar kChar)
   :KeyEvent(src, id, w, mod, kCode, kChar, KEY_LOCATION_UNKNOWN)
{
   //if(id == KEY_TYPED)
   //{
   //   if(kChar == CHAR_UNDEFINED)
   //      ex_throw new ArgumentException("invalid keyChar");
   //   
   //   if(kCode != VKEY_UNDEFINED)
   //      ex_throw new ArgumentException("invalid keyCode");
   //}
   //
   //keyLocation = KEY_LOCATION_UNKNOWN;
   //keyCode = kCode;
   //keyChar = kChar;
}

vbool KeyEvent::isAltDown()
{
   return (modifiers & ALT_MASK) != 0;
}

vbool KeyEvent::isMetaDown()
{
   return (modifiers & META_MASK) != 0;
}

vbool KeyEvent::isShiftDown()
{
   return (modifiers & SHIFT_MASK) != 0;
}

vbool KeyEvent::isActionKey()
{
   switch(keyCode)
   {
      case VKEY_HOME:
      case VKEY_END:
      case VKEY_PAGE_UP:
      case VKEY_PAGE_DOWN:
      case VKEY_UP:
      case VKEY_DOWN:
      case VKEY_LEFT:
      case VKEY_RIGHT:
      case VKEY_BEGIN:
      
	   case VKEY_KP_LEFT: 
	   case VKEY_KP_UP: 
	   case VKEY_KP_RIGHT: 
	   case VKEY_KP_DOWN: 
      
      case VKEY_F1:
      case VKEY_F2:
      case VKEY_F3:
      case VKEY_F4:
      case VKEY_F5:
      case VKEY_F6:
      case VKEY_F7:
      case VKEY_F8:
      case VKEY_F9:
      case VKEY_F10:
      case VKEY_F11:
      case VKEY_F12:
      
      case VKEY_PRINTSCREEN:
      case VKEY_SCROLL_LOCK:
      case VKEY_CAPS_LOCK:
      case VKEY_NUM_LOCK:
      case VKEY_PAUSE:
      case VKEY_INSERT:
      
      case VKEY_HELP:
      case VKEY_WINDOWS:
      case VKEY_CONTEXT_MENU:
         return true;
   }
   
   return false;
}

vbool KeyEvent::isControlDown()
{
   return (modifiers & CTRL_MASK) != 0;
}

vbool KeyEvent::isAltGraphDown()
{
   return (modifiers & ALT_GRAPH_MASK) != 0;
}

vchar KeyEvent::getKeyChar()
{
   return keyChar;
}

vint KeyEvent::getKeyCode()
{
   return keyCode;
}

vint KeyEvent::getKeyLocation()
{
   return keyLocation;
}

RString KeyEvent::getKeyText(vint keyCode)
{
   if((keyCode >= VKEY_0 && keyCode <= VKEY_9) || (keyCode >= VKEY_A && keyCode <= VKEY_Z))
      return String::valueOf((vchar)keyCode);
   
   switch(keyCode)
   {
      case VKEY_ENTER: return "Enter";
      case VKEY_BACKSPACE: return "Backspace";
      case VKEY_TAB: return "Tab";
      case VKEY_CANCEL: return "Cancel";
      case VKEY_CLEAR: return "Clear";
      case VKEY_COMPOSE: return "Compose";
      case VKEY_PAUSE: return "Pause";
      case VKEY_CAPS_LOCK: return "Caps Lock";
      case VKEY_ESCAPE: return "Escape";
      case VKEY_SPACE: return "Space";
      case VKEY_PAGE_UP: return "Page Up";
      case VKEY_PAGE_DOWN: return "Page Down";
      case VKEY_END: return "End";
      case VKEY_HOME: return "Home";
      case VKEY_LEFT: return "Left";
      case VKEY_UP: return "Up";
      case VKEY_RIGHT: return "Right";
      case VKEY_DOWN: return "Down";
      case VKEY_BEGIN: return "Begin";
      
      // modifiers 
      case VKEY_SHIFT: return "Shift";
      case VKEY_CONTROL: return "Control";
      case VKEY_ALT: return"Alt";
      case VKEY_META: return "Meta";
      case VKEY_ALT_GRAPH: return "Alt Graph";
      
      // punctuation
      case VKEY_COMMA: return "Comma";
      case VKEY_PERIOD: return "Period";
      case VKEY_SLASH: return "Slash";
      case VKEY_SEMICOLON: return "Semicolon";
      case VKEY_EQUALS: return "Equals";
      case VKEY_OPEN_BRACKET: return "Open Bracket";
      case VKEY_BACK_SLASH: return "Back Slash";
      case VKEY_CLOSE_BRACKET: return "Close Bracket";
      
      // numpad numeric keys handled below
      case VKEY_MULTIPLY: return "NumPad *";
      case VKEY_ADD: return "NumPad +";
      case VKEY_SEPARATOR: return "NumPad ,";
      case VKEY_SUBTRACT: return "NumPad -";
      case VKEY_DECIMAL: return "NumPad .";
      case VKEY_DIVIDE: return "NumPad /";
      case VKEY_DELETE: return "Delete";
      case VKEY_NUM_LOCK: return "Num Lock";
      case VKEY_SCROLL_LOCK: return "Scroll Lock";
      
      case VKEY_WINDOWS: return "Windows";
      case VKEY_CONTEXT_MENU: return "Context Menu";
      
      case VKEY_F1: return "F1";
      case VKEY_F2: return "F2";
      case VKEY_F3: return "F3";
      case VKEY_F4: return "F4";
      case VKEY_F5: return "F5";
      case VKEY_F6: return "F6";
      case VKEY_F7: return "F7";
      case VKEY_F8: return "F8";
      case VKEY_F9: return "F9";
      case VKEY_F10: return "F10";
      case VKEY_F11: return "F11";
      case VKEY_F12: return "F12";
      
      case VKEY_PRINTSCREEN: return "Print Screen";
      case VKEY_INSERT: return "Insert";
      case VKEY_HELP: return "Help";
      case VKEY_BACKQUOTE: return "Back Quote";
      case VKEY_QUOTE: return "Quote";
      
      case VKEY_KP_UP: return "Up";
      case VKEY_KP_DOWN: return "Down";
      case VKEY_KP_LEFT: return "Left";
      case VKEY_KP_RIGHT: return "Right";
      
      case VKEY_AMPERSAND: return "Ampersand";
      case VKEY_ASTERISK: return "Asterisk";
      case VKEY_QUOTEDBL: return "Double Quote";
      case VKEY_LESS: return "Less";
      case VKEY_GREATER: return "Greater";
      case VKEY_BRACE_LEFT: return "Left Brace";
      case VKEY_BRACE_RIGHT: return "Right Brace";
      case VKEY_AT: return "At";
      case VKEY_COLON: return "Colon";
      case VKEY_CIRCUMFLEX: return "Circumflex";
      case VKEY_DOLLAR: return "Dollar";
      case VKEY_EXCLAMATION: return "Exclamation Mark";
      case VKEY_LEFT_PARENTHESIS: return "Left Parenthesis";
      case VKEY_NUMBER_SIGN: return "Number Sign";
      case VKEY_MINUS: return "Minus";
      case VKEY_PLUS: return "Plus";
      case VKEY_RIGHT_PARENTHESIS: return "Right Parenthesis";
      case VKEY_UNDERSCORE: return "Underscore";
   }
    
   if(keyCode >= VKEY_NUMPAD0 && keyCode <= VKEY_NUMPAD9)
   {
      vchar c = (vchar)(keyCode - VKEY_NUMPAD0 + '0');
      
      return "Numpad-" + String::valueOf(c);
   }
   
   return "Unknown keyCode: 0x" + String::valueOf(keyCode);
}

RString KeyEvent::getKeyModifiersText(vint modifiers)
{
   RStringBuffer buf = new StringBuffer();
   
   if((modifiers & META_MASK) != 0)
      buf->append("Meta+");
   if((modifiers & CTRL_MASK) != 0)
      buf->append("Ctrl+");
   if((modifiers & ALT_MASK) != 0)
      buf->append("Alt+");
   if((modifiers & SHIFT_MASK) != 0)
      buf->append("Shift+");
   if((modifiers & ALT_GRAPH_MASK) != 0)
      buf->append("Alt Graph+");
   
   if(buf->length() > 0)
      buf->setLength(buf->length()-1); // remove trailing '+'
   
   return buf->toString();
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
