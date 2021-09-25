#include <aro/core.h>
#include <aro/util/ArrayList.h>
#include <aro/aws/FocusManager.h>
#include <aro/aws/SystemMonitor.h>
#include <aro/aws/event/KeyEvent.h>

namespace aro {

namespace aws {

using namespace event;

//class SystemMonitor;
//typedef Ref<SystemMonitor> RSystemMonitor;
//
//class SystemMonitor final : public Thread
//{
//   class Key;
//   
//   typedef Ref<Key> RKey;
//   
//   public:
//      virtual void run();
//   
//   protected:
//      virtual void finalize();
//   
//   private:
//      SystemMonitor();
//      
//      vbool monitorRunning;
//      
//      static const RArray<Key> KEYS;
//      
//      static const RSystemMonitor kde;
//      
//      class Key : public Object
//      {
//         public:
//            vint value;
//            vbool isDown;
//            
//            Key(vint value=0);
//      };
//};

//map from physical keys to character codes
const RArray<SystemMonitor::Key> SystemMonitor::KEYS = 
{
   new Key(VK_LBUTTON), new Key(VK_RBUTTON), new Key(VK_CANCEL), new Key(VK_MBUTTON),
   new Key(VK_BACK, '\b'), new Key(VK_TAB, '\t'), new Key(VK_CLEAR), new Key(VK_RETURN, '\n'),
   new Key(VK_SHIFT), new Key(VK_CONTROL), new Key(VK_MENU), new Key(VK_PAUSE), new Key(VK_CAPITAL),
   new Key(VK_ESCAPE), new Key(VK_ACCEPT), new Key(VK_SPACE,' '), new Key(VK_PRIOR), new Key(VK_NEXT),
   new Key(VK_END), new Key(VK_HOME), new Key(VK_LEFT), new Key(VK_UP), new Key(VK_RIGHT), new Key(VK_DOWN),
   new Key(VK_SELECT), new Key(VK_PRINT), new Key(VK_EXECUTE), new Key(VK_SNAPSHOT), new Key(VK_INSERT),
   new Key(VK_DELETE), new Key(VK_HELP), 
   new Key(0x30,'0',')'), new Key(0x31,'1','!'), new Key(0x32,'2','@'), new Key(0x33,'3','#'),
   new Key(0x34,'4','$'), new Key(0x35,'5','%'), new Key(0x36,'6','^'), new Key(0x37,'7','&'),
   new Key(0x38,'8','*'), new Key(0x39,'9','('), new Key(0x41,'a','A'), new Key(0x42,'b','B'),
   new Key(0x43,'c','C'), new Key(0x44,'d','D'), new Key(0x45,'e','E'), new Key(0x46,'f','F'),
   new Key(0x47,'g','G'), new Key(0x48,'h','H'), new Key(0x49,'i','I'), new Key(0x4A,'j','J'),
   new Key(0x4B,'k','K'), new Key(0x4C,'l','L'), new Key(0x4D,'m','M'), new Key(0x4E,'n','N'),
   new Key(0x4F,'o','O'), new Key(0x50,'p','P'), new Key(0x51,'q','Q'), new Key(0x52,'r','R'),
   new Key(0x53,'s','S'), new Key(0x54,'t','T'), new Key(0x55,'u','U'), new Key(0x56,'v','V'),
   new Key(0x57,'w','W'), new Key(0x58,'x','X'), new Key(0x59,'y','Y'), new Key(0x5A,'z','Z'), 
   new Key(VK_LWIN), new Key(VK_RWIN), new Key(VK_APPS),
   new Key(VK_SLEEP), new Key(VK_NUMPAD0,'0'), new Key(VK_NUMPAD1,'1'), new Key(VK_NUMPAD2,'2'),
   new Key(VK_NUMPAD3,'3'), new Key(VK_NUMPAD4,'4'), new Key(VK_NUMPAD5,'5'), new Key(VK_NUMPAD6,'6'),
   new Key(VK_NUMPAD7,'7'), new Key(VK_NUMPAD8,'8'), new Key(VK_NUMPAD9,'9'), new Key(VK_MULTIPLY,'*'),
   new Key(VK_ADD,'+'), new Key(VK_SEPARATOR), new Key(VK_SUBTRACT,'-'), new Key(VK_DECIMAL,'.'),
   new Key(VK_DIVIDE,'/'), new Key(VK_F1), new Key(VK_F2), new Key(VK_F3), new Key(VK_F4), new Key(VK_F5),
   new Key(VK_F6), new Key(VK_F7), new Key(VK_F8), new Key(VK_F9), new Key(VK_F10), new Key(VK_F11),
   new Key(VK_F12), new Key(VK_F13), new Key(VK_F14), new Key(VK_F15), new Key(VK_F16), new Key(VK_F17),
   new Key(VK_F18), new Key(VK_F19), new Key(VK_F20), new Key(VK_F21), new Key(VK_F22), new Key(VK_F23),
   new Key(VK_F24), new Key(VK_NUMLOCK), new Key(VK_SCROLL), new Key(VK_LSHIFT), new Key(VK_RSHIFT),
   new Key(VK_LCONTROL), new Key(VK_RCONTROL), new Key(VK_LMENU), new Key(VK_RMENU),
   new Key(VK_OEM_1,';',':'), new Key(VK_OEM_PLUS,'=','+'), new Key(VK_OEM_COMMA,',','<'), new Key(VK_OEM_MINUS,'-','_'),
   new Key(VK_OEM_PERIOD,'.','>'), new Key(VK_OEM_2,'/','?'), new Key(VK_OEM_3,'`','~'), new Key(VK_OEM_4,'[','{'),
   new Key(VK_OEM_5,'\\','|'), new Key(VK_OEM_6,'/','?'), new Key(VK_OEM_7,'\'','"'), new Key(VK_OEM_6,'/','?')
};

// now created by the aws::Window upon displaying first window
//const RSystemMonitor SystemMonitor::kde = new SystemMonitor();

SystemMonitor::SystemMonitor()
   :Thread("SystemMonitor")
{
   monitorRunning = false;
   
   start();
}

void SystemMonitor::run()
{
   if(monitorRunning)
      return;
   
   monitorRunning = true;
   
   vint location = 0;
   vint modifiers = 0;
   
   while(isRunning())
   {
      //for_each(RKey key, KEYS)
      for (int n=0; n<KEYS->length; n++)
      {
         RKey key = KEYS[n];

         vbool isKeyDown = (GetKeyState(key->code) < 0);
         
         location = KeyEvent::KEY_LOCATION_STANDARD;
         
         if(key->isDown != isKeyDown) // if state has changed
         {
            RComponent comp = FocusManager::getFocusManager()->getFocusOwner();

            if (comp != nullref)
            {
               key->isDown = isKeyDown;
               
               vint eventID, keyCode;
               
               vchar keyChar;
               
               if(key->isDown)
               {
                  // Checking for Typing Keys
                  if(key->standard != 0x00)
                  {
                     if((modifiers & KeyEvent::SHIFT_MASK) != 0 && key->withShift != 0x00)
                        keyChar = key->withShift;
                     else
                        keyChar = key->standard;
                     
                     eventID = KeyEvent::KEY_TYPED;
                     
                     // clear keyCode for KEY_TYPED event
                     keyCode = KeyEvent::VKEY_UNDEFINED;
                     
                     location = KeyEvent::KEY_LOCATION_UNKNOWN;
                  }
                  else
                  {
                     keyCode = key->code;
                     
                     if (keyCode >= VK_NUMPAD0 && keyCode <= VK_NUMPAD9)
                        location = KeyEvent::KEY_LOCATION_NUMPAD;
                     
                     // check for Shift modifier and location
                     else if(keyCode == VK_LSHIFT)
                     {
                        modifiers |= KeyEvent::SHIFT_MASK;
                        location = KeyEvent::KEY_LOCATION_LEFT;
                     }
                     else if(keyCode == VK_RSHIFT)
                     {
                        modifiers |= KeyEvent::SHIFT_MASK;
                        location = KeyEvent::KEY_LOCATION_RIGHT;
                     }
                     else if(keyCode == VK_SHIFT)
                     {
                        modifiers |= KeyEvent::SHIFT_MASK;
                        location = KeyEvent::KEY_LOCATION_UNKNOWN;
                     }
                  
                     // check for Ctrl modifier and location
                     else if(keyCode == VK_LCONTROL)
                     {
                        modifiers |= KeyEvent::CTRL_MASK;
                        location = KeyEvent::KEY_LOCATION_LEFT;
                     }
                     else if(keyCode == VK_RCONTROL)
                     {
                        modifiers |= KeyEvent::CTRL_MASK;
                        location = KeyEvent::KEY_LOCATION_RIGHT;
                     }
                     else if(keyCode == VK_CONTROL)
                     {
                        modifiers |= KeyEvent::CTRL_MASK;
                        location = KeyEvent::KEY_LOCATION_UNKNOWN;
                     }
                  
                     // check for Alt modifier and location
                     else if(keyCode == VK_LMENU)
                     {
                        modifiers |= KeyEvent::ALT_MASK;
                        location = KeyEvent::KEY_LOCATION_LEFT;
                     }
                     else if(keyCode == VK_RMENU)
                     {
                        modifiers |= KeyEvent::ALT_MASK;
                        location = KeyEvent::KEY_LOCATION_RIGHT;
                     }
                     else if(keyCode == VK_MENU)
                     {
                        modifiers |= KeyEvent::ALT_MASK;
                        location = KeyEvent::KEY_LOCATION_UNKNOWN;
                     }
                  
                     eventID = KeyEvent::KEY_PRESSED;
                     keyChar = KeyEvent::CHAR_UNDEFINED;
                  }
               }
               else // !key->isDown
               {
                  keyCode = key->code;
                  
                  if (keyCode >= VK_NUMPAD0 && keyCode <= VK_NUMPAD9)
                     location = KeyEvent::KEY_LOCATION_NUMPAD;
                  
                  // check for Shift modifier and location
                  else if(keyCode == VK_LSHIFT)
                  {
                     modifiers ^= KeyEvent::SHIFT_MASK;
                     location = KeyEvent::KEY_LOCATION_LEFT;
                  }
                  else if(keyCode == VK_RSHIFT)
                  {
                     modifiers ^= KeyEvent::SHIFT_MASK;
                     location = KeyEvent::KEY_LOCATION_RIGHT;
                  }
                  else if(keyCode == VK_SHIFT)
                  {
                     modifiers ^= KeyEvent::SHIFT_MASK;
                     location = KeyEvent::KEY_LOCATION_UNKNOWN;
                  }
               
                  // check for Ctrl modifier and location
                  else if(keyCode == VK_LCONTROL)
                  {
                     modifiers ^= KeyEvent::CTRL_MASK;
                     location = KeyEvent::KEY_LOCATION_LEFT;
                  }
                  else if(keyCode == VK_RCONTROL)
                  {
                     modifiers ^= KeyEvent::CTRL_MASK;
                     location = KeyEvent::KEY_LOCATION_RIGHT;
                  }
                  else if(keyCode == VK_CONTROL)
                  {
                     modifiers ^= KeyEvent::CTRL_MASK;
                     location = KeyEvent::KEY_LOCATION_UNKNOWN;
                  }
               
                  // check for Alt modifier and location
                  else if(keyCode == VK_LMENU)
                  {
                     modifiers ^= KeyEvent::ALT_MASK;
                     location = KeyEvent::KEY_LOCATION_LEFT;
                  }
                  else if(keyCode == VK_RMENU)
                  {
                     modifiers ^= KeyEvent::ALT_MASK;
                     location = KeyEvent::KEY_LOCATION_RIGHT;
                  }
                  else if(keyCode == VK_MENU)
                  {
                     modifiers ^= KeyEvent::ALT_MASK;
                     location = KeyEvent::KEY_LOCATION_UNKNOWN;
                  }
               
                  keyChar = KeyEvent::CHAR_UNDEFINED;
               
                  eventID = KeyEvent::KEY_RELEASED;
               }
               
               RKeyEvent rke = new KeyEvent(comp, eventID, System::currentTime(),
                                 modifiers, keyCode, keyChar, location);
               
               System::getEventQueue()->postEvent(rke);
            }
         }
      }
      
      sleep(100); // 1/10th of a second, i.e. max of 10 key events per second.
   }
}

vbool SystemMonitor::isRunning()
{
   return monitorRunning;
}

void SystemMonitor::finalize()
{
   stop();
   
   Thread::finalize();
}

void SystemMonitor::stop()
{
   monitorRunning = false;
}

SystemMonitor::Key::Key(vint keyCode)
   :Key(keyCode, 0)
{
   
}

SystemMonitor::Key::Key(vint keyCode, vchar alone)
   :Key(keyCode, alone, 0)
{
   
}

SystemMonitor::Key::Key(vint keyCode, vchar alone, vchar shift)
   :Key(keyCode, alone, shift, 0)
{
   
}

SystemMonitor::Key::Key(vint keyCode, vchar alone, vchar shift, vchar cntrl)
   : Key(keyCode, alone, shift, cntrl, 0)
{
   
}

SystemMonitor::Key::Key(vint keyCode, vchar alone, vchar shift, vchar cntrl, vchar cntrlShift)
{
   code = keyCode;
   standard = alone;
   withShift = shift;
   withControl = cntrl;
   withControlShift = cntrlShift;
   
   isDown = GetKeyState(code) < 0;
}

} /* namespace aws */

} /* namespace aro */
