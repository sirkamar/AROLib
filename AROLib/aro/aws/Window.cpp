#include <conio.h>
#include <cstdlib>
#include <aro/core.hpp>
#include <aro/aws/Frame.hpp>
#include <aro/aws/Dialog.hpp>
#include <aro/aws/Window.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/ZoneLayout.hpp>
#include <aro/aws/FocusPolicy.hpp>
#include <aro/aws/FocusManager.hpp>
#include <aro/aws/SystemMonitor.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/aws/event/WindowEvent.hpp>
#include <aro/aws/event/FocusCausedEvent.hpp>

namespace aro {

namespace aws {

using namespace event;

RSystemMonitor sysMonitor;

vint visibleWindowCount = 0;

util::RVector<Weak<Window>> windowList;

const RObject WINDOW_CLASS = new Object();

Window::Window()
   :Window(nullref)
{
   
}

Window::Window(RWindow owner)
{
   ownedWindowList = new util::Vector<Weak<Window>>();
   
   RWindow thisWindow = this; // keep alive

   weakThis = new Weak<Window>(thisWindow);
   
   focusableWindowState = true;
   
   manager = new ZoneLayout();
   
   addToWindowList();
   
   running = false;
   visible = false;
   isInShow = false;
   focusable = true;
   disposing = false;
   beforeFirstShow = true;
   
   if(owner != nullref)
   {
      owner->addOwnedWindow(weakThis);
      
      this->owner = new Weak<Window>(owner);
   }
}

void Window::pack()
{
   if(beforeFirstShow)
      isPacked = true;

   validateUnconditionally();
}

void Window::dispose()
{
   doDispose();
}

void Window::doDispose()
{
   vbool fireWindowClosed = isDisplayable();
   
   running = false;
   
   disposing = true;

   RArray<Weak<Window>> ownedWindowArray;

   sync_lock(ownedWindowList)
   {
      ownedWindowArray = ownedWindowList->toArray();
   }

   for(RWeak<Window> rw : ownedWindowArray)
   {
      RWindow child = rw->get();

      if(child != nullref)
         child->disposeImpl();
   }

   hide();

   beforeFirstShow = true;

   //clearCurrentFocusCycleRootOnHide();
   
   if(owner != nullref)
   {
      RWindow parent = owner->get();
      if (parent != nullref)
         parent->removeOwnedWindow(weakThis);
      owner = nullref;
   }
   
   disposing = false;

   if(runner != nullref)
   {
      runner->stop();
      runner = nullref;
   }

   if(fireWindowClosed)
      postWindowEvent(WindowEvent::WINDOW_CLOSED);
}

void Window::disposeImpl()
{
   dispose();

   if(runner != nullref)
      doDispose();
}

void Window::addToWindowList()
{
   sync_lock(WINDOW_CLASS)
   {
      if(windowList == nullref)
      {
         //sysMonitor = new SystemMonitor();
         
         windowList = new util::Vector<Weak<Window>>();
         
         //sysMonitor->setPriority(Thread::PRIORITY_HIGHEST);
      }
      
      windowList->add(weakThis);
   }
}

void Window::removeFromWindowList()
{
   sync_lock(WINDOW_CLASS)
   {
      if(windowList != nullref)
      {
         windowList->remove(weakThis);

         if(windowList->isEmpty())
         {
            sysMonitor->stop();
            sysMonitor = nullref;
            windowList = nullref;
         }
      }
   }
}

void Window::postWindowEvent(vint eventID)
{
   sync_lock(thisref)
   {
      RWindowEvent e = new WindowEvent(thisref, eventID);
      
      System::getEventQueue()->postEvent(e);
   }
}

void Window::hide()
{
   sync_lock(ownedWindowList)
   {
      for(RWeak<Window> rw : ownedWindowList)
      {
         RWindow child = rw->get();
         if(child != nullref && child->visible)
            child->hide();
      }
   }
   
   visibleWindowCount--;
   
   if(visibleWindowCount == 0)
   {
      sysMonitor->stop();
      sysMonitor = nullref;
   }
   
   Container::hide();
}

void Window::show()
{
   validateUnconditionally();

   isInShow = true;

   if(visible)
      ;//toFront();
   else
   {
      beforeFirstShow = false;
      
      Container::show();
      
      visibleWindowCount++;
      
      if(visibleWindowCount == 1)
         sysMonitor = new SystemMonitor();
      
      for(RWeak<Window> rw: ownedWindowList)
      {
         RWindow child = rw->get();
         if(child != nullref)
            child->show();
      }
   }

   isInShow = false;

   //if first time shown, generate WindowOpened event
   if((state & 0x01) == 0)
   {
      postWindowEvent(WindowEvent::WINDOW_OPENED);
      state |= 0x01;
   }
}

vbool Window::isActive()
{
   return (FocusManager::getFocusManager()->getActiveWindow() == thisref);
}

vbool Window::isFocused()
{
   return (FocusManager::getFocusManager()->getFocusedWindow() == thisref);
}

vbool Window::isShowing()
{
   return visible;
}

void Window::repaint()
{
   Container::repaint(x, y, width, height);
}

RWindow Window::getOwner()
{
   return type_cast<Window>(getParent());
}

void Window::setVisible(vbool b)
{
   //if (b && !running)
   //{
   //   runner = new WinRunThread(thisref);
   //   
   //   runner->start();
   //}
   
   Container::setVisible(b);
}

vbool Window::isFocusableWindow()
{
   if(!getFocusableWindowState())
      return false;
   
   if(type_of<Frame>(thisref) || type_of<Dialog>(thisref))
      return true;
   
   if(getFocusPolicy()->getDefault(thisref) == nullref)
      return false;
   
   for(RWindow own = getOwner(); own != nullref; own = own->getOwner())
      if(type_of<Frame>(own) || type_of<Dialog>(own))
         return own->isShowing();
   
   return false;
}

vbool Window::getFocusableWindowState()
{
   return focusableWindowState;
}

void Window::setFocusableWindowState(vbool b)
{
   vbool oldState = focusableWindowState;
   focusableWindowState = b;
   
   if(oldState && !focusableWindowState && isFocused())
   {
      for(RWindow own = getOwner(); own != nullref; own = own->getOwner())
      {
         RComponent toFocus = FocusManager::getMostRecentFocusOwner(own);
         
		 if(toFocus != nullref && toFocus->requestFocus(false, FocusCausedEvent::Cause::ACTIVATION))
            return;
      }
      
      FocusManager::getFocusManager()->setFocusOwner(nullref);
   }
}

RComponent Window::getFocusOwner()
{
   return isFocused() ?
      FocusManager::getFocusManager()->getFocusOwner() : nullref ;
}

RFocusPolicy Window::getFocusPolicy()
{
   return FocusManager::getFocusManager()->getFocusPolicy();
}

void Window::addWindowListener(RWindowListener l)
{
   listeners->add<WindowListener>(l);
}

void Window::removeWindowListener(RWindowListener l)
{
   listeners->remove<WindowListener>(l);
}

void Window::addWindowFocusListener(RWindowFocusListener l)
{
   listeners->add<WindowFocusListener>(l);
}

void Window::removeWindowFocusListener(RWindowFocusListener l)
{
   listeners->remove<WindowFocusListener>(l);
}

RComponent Window::getMostRecentFocusOwner()
{
   if(isFocused())
      return getFocusOwner();
   else
   {
      RComponent mostRecent = FocusManager::getMostRecentFocusOwner(thisref);

      if(mostRecent != nullref)
         return mostRecent;
      else
      {
         RFocusManager mngr = FocusManager::getFocusManager();

         return isFocusableWindow() ?
            mngr->getFocusPolicy()->getDefault(thisref) : nullref;
      }
   }
}

RComponent Window::getTemporaryLostComponent()
{
   return temporaryLostComp;
}

RComponent Window::setTemporaryLostComponent(RComponent comp)
{
   RComponent previous = temporaryLostComp;

   if(comp == nullref || comp->canBeFocusOwner())
      temporaryLostComp = comp;
   else
      temporaryLostComp = nullref;
   
   return previous;
}

void Window::processEvent(RAWSEvent e)
{
   if(type_of<WindowEvent>(e))
   {
      switch(e->getEventID())
      {
         case WindowEvent::WINDOW_OPENED:
         case WindowEvent::WINDOW_CLOSING:
         case WindowEvent::WINDOW_CLOSED:
         case WindowEvent::WINDOW_ACTIVATED:
         case WindowEvent::WINDOW_DEACTIVATED:
            processWindowEvent(type_cast<WindowEvent>(e));
            break;

         case WindowEvent::WINDOW_GOT_FOCUS:
         case WindowEvent::WINDOW_LOST_FOCUS:
            processWindowFocusEvent(type_cast<WindowEvent>(e));
            break;
      }

      return;
   }

   Container::processEvent(e);
}

void Window::processWindowEvent(RWindowEvent e)
{
   fireWindowEvent(e);
}

void Window::processWindowFocusEvent(RWindowEvent e)
{
   
}

void Window::postProcessKeyEvent(RKeyEvent e)
{
   if(e->getEventID() == KeyEvent::KEY_RELEASED && e->getKeyCode() == KeyEvent::VKEY_ESCAPE)
   {
      postWindowEvent(WindowEvent::WINDOW_CLOSING);
      
      e->consume();
   }
}

void Window::fireWindowEvent(RWindowEvent e)
{
   vint eventID = e->getEventID();
   
   RArray<util::Listener> arr = listeners->getListeners();
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<WindowListener>(arr[n]))
      {
         RWindowListener rwl = type_cast<WindowListener>(arr[n]);
         
         if(eventID == WindowEvent::WINDOW_CLOSING)
            rwl->windowClosing(e);
         else if(eventID == WindowEvent::WINDOW_CLOSED)
            rwl->windowClosed(e);
         else if(eventID == WindowEvent::WINDOW_OPENED)
            rwl->windowOpened(e);
      }
   }
}

void Window::paint(RGraphics g)
{
   Container::paint(g);
}

void Window::connectOwnedWindow(RWindow child)
{
   child->parent = thisref;
   addOwnedWindow(child->weakThis);

   RWindow victim = child->weakThis->get();
   if(victim == nullref)
      child->owner = nullref;
   else
      child->owner = new Weak<Window>(victim->getOwner());
}

void Window::addOwnedWindow(RWeak<Window> win)
{
   if(win != nullref)
   {
      sync_lock(ownedWindowList)
      {
         if(!ownedWindowList->contains(win))
         {
            ownedWindowList->addElement(win);
         }
      }
   }
}

void Window::removeOwnedWindow(RWeak<Window> win)
{
   if(win != nullref)
   {
      ownedWindowList->removeElement(win);
   }
}

void Window::finalize()
{
   if(runner != nullref)
   {
      runner->stop();
      
      runner = nullref;
   }
   
   if(sysMonitor != nullref)
      sysMonitor->stop();
   
   removeFromWindowList();

   Container::finalize();
}

Window::WinRunThread::WinRunThread(RWindow w)
{
   running = false;
   window = w;
}

void Window::WinRunThread::finalize()
{
   stop();
   
   Thread::finalize();
}

void Window::WinRunThread::stop()
{
   window = nullref;
   running = false;
}

void Window::WinRunThread::run()
{
   running = true;
   
   while(running)
   {
      Thread::sleep(250L);
   }
}

} /* namespace aws */

} /* namespace aro */
