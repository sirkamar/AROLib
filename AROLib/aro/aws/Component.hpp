#ifndef AWS_COMPONENT_H
#define AWS_COMPONENT_H

#include <aro/aws/Dimension.hpp>
#include <aro/aws/EventQueue.hpp>
#include <aro/aws/ListenerList.hpp>
#include <aro/aws/SystemMonitor.hpp>
#include <aro/aws/event/KeyListener.hpp>
#include <aro/aws/event/FocusListener.hpp>
#include <aro/aws/event/FocusCausedEvent.hpp>
#include <aro/aws/event/PropertyListener.hpp>
#include <aro/aws/event/ComponentListener.hpp>

namespace aro {

namespace aws {

class Point;
class Window;
class AWSEvent;
class Container;
class Rectangle;

// reference type definitions
typedef Ref<Point> RPoint;
typedef Ref<Window> RWindow;
typedef Ref<AWSEvent> RAWSEvent;
typedef Ref<Container> RContainer;
typedef Ref<Rectangle> RRectangle;
// Component and RComponent pre-declared in aro/aws/Border.h

/** A component is an object having a graphical
 * representation that can be displayed on the
 * screen and that a user can interact with.
 * Examples of components are the buttons,
 * labels and textboxes of a typical gui.
 * The Component class is the base class
 * of all of the user interface classes. */
class Component extends public Object
{
   public:
      virtual void requestFocus();
      virtual void setVisible(vbool b);
      virtual void setEnabled(vbool b);
      virtual void setFocusable(vbool b);
      virtual vbool requestFocusInWindow();
      virtual void setSize(RDimension size);
      virtual void setLocation(RPoint pos);
      virtual void setLocation(vint x,vint y);
      virtual void setBounds(RRectangle bounds);
      virtual void setMaximumSize(RDimension max);
      virtual void setMinimumSize(RDimension min);
      virtual void setSize(vint width,vint height);
      virtual void setPreferredSize(RDimension size);
      virtual void addKeyListener(event::RKeyListener l);
      virtual void addFocusListener(event::RFocusListener l);
      virtual void addPropertyListener(event::RPropertyListener l);
      virtual void addComponentListener(event::RComponentListener l);
      virtual void setBounds(vint x,vint y,vint width,vint height);
      
      virtual void removeComponentListener(event::RComponentListener l);
      virtual void removePropertyListener(event::RPropertyListener l);
      virtual void removeFocusListener(event::RFocusListener l);
      virtual void removeKeyListener(event::RKeyListener l);
      virtual RDimension getPreferredSize();
      virtual RDimension getMinimumSize();
      virtual RDimension getMaximumSize();
      virtual RRectangle getBounds();
      virtual RDimension getSize();
      virtual RPoint getLocation();
      virtual vbool isDisplayable();
      virtual vbool isFocusOwner();
      virtual vbool isFocusable();
      virtual vbool isFocused();
      virtual vbool isEnabled();
      virtual vbool isVisible();
      
      virtual vbool isParentWindow(RContainer w);
      virtual void transferFocusBackward();
      virtual RWindow getParentWindow();
      virtual vbool isPreferredSizeSet();
      virtual vbool isMaximumSizeSet();
      virtual vbool isMinimumSizeSet();
      virtual RContainer getParent();
      virtual void transferFocus();
      virtual void invalidate();
      virtual vbool isShowing();
      virtual void validate();
      virtual vint getHeight();
      virtual vint getWidth();
      virtual vbool isValid();
      virtual vint getX();
      virtual vint getY();
      
      virtual void repaint();
      //each component paints itself but
      //but should call the paint function
      //of it's immediate base class as the
      //first statement of its paint function
      //so as to properly clear the component.
      virtual void update(RGraphics g);
      virtual void paint(RGraphics g)=0;
      virtual void paintAll(RGraphics g);

      virtual RObject getTreeLock() final;
      virtual vbool canBeFocusOwner(RComponent);
      virtual void dispatchEvent(RAWSEvent e) final;
      virtual void repaint(vint x, vint y, vint width, vint height);

      virtual RArray<event::ComponentListener> getComponentListeners();
      virtual RArray<event::PropertyListener> getPropertyListeners();
      virtual RArray<event::FocusListener> getFocusListeners();
      virtual RArray<event::KeyListener> getKeyListeners();
      
      static RWindow getParentWindow(RComponent comp);
   
   protected:
      RListenerList listeners;
      
      Component();

      virtual void hide();
      virtual void show();
      virtual void revalidate();
      
      virtual void processEvent(RAWSEvent e);
      virtual void processKeyEvent(event::RKeyEvent e);
      virtual void processFocusEvent(event::RFocusEvent e);
      virtual void processComponentEvent(event::RComponentEvent e);
      
      virtual vbool canBeFocusOwner() final;
      virtual vbool requestFocus(vbool temp);
      virtual vbool requestFocusInWindow(vbool temp);
      
      void autoTransferFocus(vbool clearOnFail);
      vbool requestFocus(event::FocusCausedEvent::RCause cause);
      vbool requestFocusInWindow(event::FocusCausedEvent::RCause cause);
      vbool requestFocusHelper(vbool temp, vbool change, event::FocusCausedEvent::RCause cause);
      
      void firePropertyChanged(RString propertyName, RObject oldVal, RObject newVal);
   
   private:
      vbool focus;
      vbool valid;
      vbool visible;
      vbool enabled;
      vbool isPacked;
      vbool focusable;
      RContainer parent;
      vint x, y, width, height;
      RDimension max, min, prefer;
      vbool minSet, maxSet, prefSet;
      
      RArray<EventQueue::QueueItem> eventCache;

      static const RObject LOCK;
      
      vbool transferFocusHelper();
      void doAutoTransfer(vbool clearOnFail);
      vbool requestFocus(vbool temp, event::FocusCausedEvent::RCause cause);
      vbool requestFocusInWindow(vbool temp, event::FocusCausedEvent::RCause cause);
      vbool isRequestFocusAccepted(vbool temp, vbool change, event::FocusCausedEvent::RCause cause);
   
   friend class Window;
   friend class Container;
   friend class EventQueue;
   friend class DefaultFocusManager;
};

} /* namespace aws */

} /* namespace aro */

#include <aro/aws/Container.hpp>

#endif /* AWS_COMPONENT_H */
