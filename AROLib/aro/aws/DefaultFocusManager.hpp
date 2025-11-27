#ifndef AWS_DEFAULTFOCUSMANAGER_H
#define AWS_DEFAULTFOCUSMANAGER_H

#include <aro/aws/FocusManager.hpp>

namespace aro {

namespace aws {

class DefaultFocusManager;
typedef Ref<DefaultFocusManager> RDefaultFocusManager;

class DefaultFocusManager extends public FocusManager
{
   class TypeAheadMarker;
   typedef Ref<TypeAheadMarker> RTypeAheadMarker;

   class TypeAheadMarker : public Object
   {
      public:
         vlong after;
         RComponent untilFocused;
         
         TypeAheadMarker(vlong after, RComponent untilFocused);
   };
   
   public:
      DefaultFocusManager();
      
      virtual vbool dispatchEvent(RAWSEvent e);
      virtual vbool dispatchKeyEvent(event::RKeyEvent e);
      virtual vbool postProcessKeyEvent(event::RKeyEvent e);
      virtual void processKeyEvent(RComponent comp, event::RKeyEvent e);

      virtual void focusNextComponent(RComponent current);
      virtual void focusPreviousComponent(RComponent current);
   
   protected:
      virtual void discardKeyEvents(RComponent comp);
      virtual void dequeueKeyEvents(vlong after, RComponent untilFocused);
      virtual void enqueueKeyEvents(vlong after, RComponent untilFocused);
   
   private:
      vint inSendMessage;
      vbool consumeNextTypedKey;
      RWeak<Window> realOppositeWindow;
      RWeak<Component> realOppositeComponent;
      util::RLinkedList<event::KeyEvent> enqueuedKeyEvents;
      util::RLinkedList<TypeAheadMarker> typeAheadMarkers;

      static const RWeak<Window> NULL_WINDOW_WR;
      static const RWeak<Component> NULL_COMPONENT_WR;

      void clearMarkers();
      void pumpApprovedKeyEvents();
      vbool hasMarker(RComponent comp);
      void restoreFocus(event::RWindowEvent we);
      RWindow getOwningFrameDialog(RWindow window);
      void consumeNextKeyTyped(event::RKeyEvent e);
      void consumeTraversalKey(event::RKeyEvent e);
      vbool preDispatchKeyEvent(event::RKeyEvent e);
      void purgeStampedEvents(vlong start, vlong end);
      vbool consumeProcessedKeyEvent(event::RKeyEvent e);
      static vbool sendMessage(RComponent target, RAWSEvent e);
      vbool typeAheadAssertions(RComponent target, RAWSEvent e);
      vbool restoreFocus(RComponent toFocus, vbool clearOnFailure);
      void restoreFocus(event::RFocusEvent fe, RWindow newFocusedWindow);
      vbool restoreFocus(RWindow aWindow, RComponent vetoedComponent, vbool clearOnFailure);
      vbool doRestoreFocus(RComponent toFocus, RComponent vetoedComponent, vbool clearOnFailure);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_DEFAULTFOCUSMANAGER_H */
