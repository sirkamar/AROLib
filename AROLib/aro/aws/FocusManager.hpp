#ifndef AWS_FOCUSMANAGER_H
#define AWS_FOCUSMANAGER_H

#include <aro/util/Map.hpp>
#include <aro/aws/Window.hpp>
#include <aro/aws/KeyStroke.hpp>
#include <aro/aws/FocusPolicy.hpp>
#include <aro/util/LinkedList.hpp>
#include <aro/aws/event/FocusCausedEvent.hpp>

namespace aro {

namespace aws {

class KeyStroke;
class FocusManager;
typedef Ref<FocusManager> RFocusManager;

class FocusManager extends public Object
{
   public:
      static const vint FOCUS_NEXT_KEYS;
      static const vint FOCUS_PREV_KEYS;
      
      FocusManager();
      
      void focusNextComponent();
      void focusPreviousComponent();
      void redispatchEvent(RComponent c, RAWSEvent e);
      RArray<event::PropertyListener> getPropertyListeners();
      virtual void addPropertyListener(event::RPropertyListener l);
      virtual void removePropertyListener(event::RPropertyListener l);
      
      virtual void clearFocusOwner();
      virtual RWindow getActiveWindow();
      virtual RWindow getFocusedWindow();
      virtual RComponent getFocusOwner();
      virtual RFocusPolicy getFocusPolicy();
      virtual RComponent getPermanentFocusOwner();
      virtual RContainer getCurrentFocusCycleRoot();
      virtual util::RList<KeyStroke> getFocusTraversalKeys(vint id);
      
      virtual void setActiveWindow(RWindow win);
      virtual void setFocusedWindow(RWindow win);
      virtual void setFocusOwner(RComponent comp);
      virtual void setFocusPolicy(RFocusPolicy policy);
      virtual void setPermanentFocusOwner(RComponent comp);
      virtual void setCurrentFocusCycleRoot(RContainer root);
      virtual void setFocusTraversalKeys(vint id, util::RList<KeyStroke> keys);
      
      static RFocusManager getFocusManager();
      static void setFocusManager(RFocusManager manager);
      
      vbool focusComponent(RComponent target, vbool temp,
                           vbool changeAllowed, event::FocusCausedEvent::RCause cause);
      
      static void setMostRecentFocusOwner(RComponent comp);
      static void clearMostRecentFocusOwner(RComponent comp);
      static RComponent getMostRecentFocusOwner(RWindow win);
      static void setMostRecentFocusOwner(RWindow win, RComponent comp);
      
      static vbool hasFocusRequests();
      static vbool removeFirstRequest();
      static void processCurrentRequests();
      static RWindow markClearFocusOwner();
      RComponent getFocusRequest(RComponent parent);
      static RAWSEvent retargetFocusEvent(RAWSEvent e);
      static void removeLastFocusRequest(RComponent comp);
      static event::RFocusEvent retargetGotFocus(event::RFocusEvent fe);
      static event::RFocusEvent retargetLostFocus(event::RFocusEvent fe);
      static event::RFocusEvent retargetUnexpectedFocusEvent(event::RFocusEvent fe);
      static void addFocusRequest(RComponent parent, RComponent child, vbool temp,
                                             event::FocusCausedEvent::RCause cause);
      
      virtual vbool dispatchEvent(RAWSEvent e)=0;
      virtual vbool dispatchKeyEvent(event::RKeyEvent e) = 0;
      virtual vbool postProcessKeyEvent(event::RKeyEvent e) = 0;
      virtual void focusNextComponent(RComponent current)=0;
      virtual void focusPreviousComponent(RComponent current)=0;
      virtual void processKeyEvent(RComponent comp, event::RKeyEvent e) = 0;
   
   protected:
      RListenerList listeners;
      static vbool disableRestore;
      static const RObject CLASS_LOCK;

      virtual void discardKeyEvents(RComponent comp)=0;
      virtual void enqueueKeyEvents(vlong after, RComponent untilFocused)=0;
      virtual void dequeueKeyEvents(vlong after, RComponent untilFocused)=0;

      void firePropertyChanged(RString name, RObject oldValue, RObject newValue);
   
   private:
      RFocusPolicy policy;
      RArray<util::List<KeyStroke>> focusTraversalKeys;
      static const RArray2D<KeyStroke> defaultFocusTraversalKeys;
      
      static RWindow activeWindow;
      static RWindow focusedWindow;
      static RComponent focusOwner;
      static RFocusManager manager;
      static RComponent permanentFocusOwner;
      static RContainer currentFocusCycleRoot;
      
      class FocusRequest;
      typedef Ref<FocusRequest> RFocusRequest;
      
      static vbool clearingCurrent;
      static vbool allowSyncRequests;
      static RComponent newFocusOwner;
      static RFocusRequest currentRequest;
      static util::RLinkedList<FocusRequest> focusRequests;
      
      static vbool isTemporary(RComponent to, RComponent from);
      static vbool focusedWindowChanged(RComponent to, RComponent from);

      static util::RMap<Window, Weak<Component>> mostRecentFocusOwners;
};

class FocusManager::FocusRequest : public Object
{
   public:
      const vbool temporary;
      const RComponent comp;
      const event::FocusCausedEvent::RCause cause;
      
      static const RFocusRequest CLEAR_FOCUS_OWNER;
      
      FocusRequest(RComponent c, vbool temp, event::FocusCausedEvent::RCause cause);
   
   private:
      FocusRequest();
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_FOCUSMANAGER_H */
