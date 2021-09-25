#include <aro/core.h>
#include <aro/aws/KeyStroke.h>
#include <aro/aws/event/KeyEvent.h>
#include <aro/util/ArrayList.h>

namespace aro {

namespace aws {

using namespace util;
using namespace event;

RKeyStroke KeyStroke::cacheKey;
RList<KeyStroke> KeyStroke::cache;

KeyStroke::KeyStroke()
{
   keyChar = KeyEvent::CHAR_UNDEFINED;
   keyCode = KeyEvent::VKEY_UNDEFINED;
   modifiers = 0;
   onRelease = false;
}

KeyStroke::KeyStroke(vchar keyChar, vint keyCode, vint modifiers, vbool onRelease)
{
   thisref->keyChar = keyChar;
   thisref->keyCode = keyCode;
   thisref->modifiers = modifiers;
   thisref->onRelease = onRelease;
}

RKeyStroke KeyStroke::getCachedKeyStroke(vchar keyChar, vint keyCode, vint modifiers, vbool onRelease)
{
   if(cache == nullref)
      cache = new ArrayList<KeyStroke>();
   
   if(cacheKey == nullref)
      cacheKey = new KeyStroke();
   
   cacheKey->keyChar = keyChar;
   cacheKey->keyCode = keyCode;
   cacheKey->modifiers = modifiers;
   cacheKey->onRelease = onRelease;
   
   RKeyStroke stroke = nullref;
   
   if(cache->contains(cacheKey))
      stroke = cache->get(cache->indexOf(cacheKey));
   else
   {
      stroke = cacheKey;
      cache->add(stroke);
      cacheKey = nullref;
   }
   
   return stroke;
}

RKeyStroke KeyStroke::getKeyStroke(vchar keyChar)
{
   return getCachedKeyStroke(keyChar, KeyEvent::VKEY_UNDEFINED, 0, false);
}

RKeyStroke KeyStroke::getKeyStroke(vint keyCode, vint modifiers)
{
   return getCachedKeyStroke(KeyEvent::CHAR_UNDEFINED, keyCode, modifiers, false);
}

RKeyStroke KeyStroke::getKeyStroke(RChar keyChar, vint modifiers)
{
   if(keyChar == nullref)
      ex_throw new ArgumentException("keyChar cannot be null");
   
   return getCachedKeyStroke(keyChar->charValue(), KeyEvent::VKEY_UNDEFINED, modifiers, false);
}

RKeyStroke KeyStroke::getKeyStroke(vint keyCode, vint modifiers, vbool onRelease)
{
   return getCachedKeyStroke(KeyEvent::CHAR_UNDEFINED, keyCode, modifiers, onRelease);
}

RKeyStroke KeyStroke::getKeyStroke(vchar keyChar, vint keyCode, vint modifiers, vbool onRelease)
{
   return getCachedKeyStroke(keyChar, keyCode, modifiers, onRelease);
}

RKeyStroke KeyStroke::getKeyStrokeForEvent(RKeyEvent e)
{
   vint id = e->getEventID();
   
   if(id == KeyEvent::KEY_PRESSED || id == KeyEvent::KEY_RELEASED)
         return getCachedKeyStroke(KeyEvent::CHAR_UNDEFINED,
                e->getKeyCode(), e->getModifiers(),
                (id == KeyEvent::KEY_RELEASED));
   
   if(id == KeyEvent::KEY_TYPED)
         return getCachedKeyStroke(e->getKeyChar(),
               KeyEvent::VKEY_UNDEFINED,
               e->getModifiers(), false);
   
   return nullref; // Invalid ID for this KeyEvent
}

vbool KeyStroke::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<KeyStroke>(obj))
   {
      RKeyStroke stroke = type_cast<KeyStroke>(obj);
      
      return (keyChar == stroke->keyChar && keyCode == stroke->keyCode &&
         modifiers == stroke->modifiers && onRelease == stroke->onRelease);
   }
   
   return false;
}

vint KeyStroke::getKeyEventType()
{
   if(keyCode == KeyEvent::VKEY_UNDEFINED)
      return KeyEvent::KEY_TYPED;
   
   if(onRelease)
      return KeyEvent::KEY_RELEASED;
   
   return KeyEvent::KEY_PRESSED;
}

vbool KeyStroke::isOnRelease()
{
   return onRelease;
}

vint KeyStroke::getModifiers()
{
   return modifiers;
}

vchar KeyStroke::getKeyChar()
{
   return keyChar;
}

vint KeyStroke::getKeyCode()
{
   return keyCode;
}

} /* namespace aws */

} /* namespace aro */
