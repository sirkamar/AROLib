#include <aro/core.h>
#include <aro/aws/Point.h>
#include <aro/aws/Frame.h>
#include <aro/aws/Dialog.h>
#include <aro/aws/Window.h>
#include <aro/aws/Component.h>
#include <aro/aws/Container.h>
#include <aro/aws/Rectangle.h>
#include <aro/aws/FocusPolicy.h>
#include <aro/aws/FocusManager.h>
#include <aro/aws/event/all.h>

namespace aro {

namespace aws {

using namespace event;

const RObject Component::LOCK = new Object();

Component::Component()
{
   x = y = 0;
   isPacked = false;
   width = height = 1;
   focus = valid = false;
   listeners = new ListenerList();
   maxSet = minSet = prefSet = false;
   focusable = enabled = visible = true;
}

RContainer Component::getParent()
{
   return parent;
}

RObject Component::getTreeLock()
{
   return LOCK;
}

vbool Component::isValid()
{
   return valid;
}

vbool Component::isShowing()
{
   if(!visible)
      return false;
   
   return (parent != nullref && parent->isShowing());
}

vbool Component::isVisible()
{
   return visible;
}

vbool Component::isEnabled()
{
   return enabled;
}

void Component::setEnabled(vbool b)
{
   if(enabled != b) // state changed
   {
      if(enabled) // then disable
      {
         FocusManager::clearMostRecentFocusOwner(thisref);
         
         sync_lock(getTreeLock())
         {
            enabled = false;
            
            // Don't clear the focus owner. If transferFocus
            // fails, we want the focus to stay on the disabled
            // Component so that keyboard traversal, et. al. still
            // makes sense to the user.
            if(isFocusOwner())
               autoTransferFocus(false);
            
            // consider moving cursor if CSTextComponent
            // and/or changing the appearance
         }
      }
      else // change to enabled
      {
         sync_lock(getTreeLock())
         {
            enabled = true;
         }
      }
      
      firePropertyChanged("enabled", Bool::valueOf(!b), Bool::valueOf(b));
      
      repaint();
   }
}

void Component::setVisible(vbool b)
{
   if(b)
      show();
   else
      hide();
}

void Component::hide()
{
   isPacked = false;

   if(visible)
   {
      //clearCurrentFocusCycleRootOnHide();
      //clearMostRecentFocusOwnerOnHide();
      FocusManager::clearMostRecentFocusOwner(thisref);

      sync_lock(getTreeLock())
      {
         visible = false;

         if(isFocusOwner())
            autoTransferFocus(true);

         repaint();
         
         event::RComponentEvent e = new ComponentEvent(thisref,
                                    ComponentEvent::COMPONENT_HIDDEN);
         
         System::getEventQueue()->postEvent(e);
      }
      
      RContainer parent = thisref->parent;
      
      if(parent != nullref)
         parent->invalidate();
   }
}

void Component::show()
{
   if(!visible)
   {
      sync_lock(getTreeLock())
      {
         visible = true;

         repaint();
         
         event::RComponentEvent e = new ComponentEvent(thisref,
                                    ComponentEvent::COMPONENT_SHOWN);
         
         System::getEventQueue()->postEvent(e);
      }
      
      RContainer parent = thisref->parent;
      
      if(parent != nullref)
         parent->invalidate();
   }
}

RPoint Component::getLocation()
{
   return new Point(x, y);
}

void Component::setLocation(RPoint p)
{
   setLocation(p->x, p->y);
}

void Component::setLocation(vint xP, vint yP)
{
   setBounds(xP, yP, width, height);
}

RDimension Component::getSize()
{
   return new Dimension(width, height);
}

void Component::setSize(RDimension d)
{
   setSize(d->width, d->height);
}

void Component::setSize(vint wD, vint hD)
{
   setBounds(x, y, wD, hD);
}

RRectangle Component::getBounds()
{
   return new class Rectangle(x, y, width, height);
}

void Component::setBounds(RRectangle r)
{
   setBounds(r->x, r->y, r->width, r->height);
}

void Component::setBounds(vint xP, vint yP, vint wD, vint hD)
{
   sync_lock(getTreeLock())
   {
      vbool moved = (x != xP) || (y != yP);
      vbool resized = (width != wD) || (height != hD);
      
      if(moved || resized)
      {
         vint oldX = x, oldY = y, oldW = width, oldH = height;
         x = xP; y = yP; width = wD; height = hD;
         
         if(resized)
            invalidate();
      }
   }
}

vint Component::getX()
{
   return x;
}

vint Component::getY()
{
   return y;
}

vint Component::getWidth()
{
   return width;
}

vint Component::getHeight()
{
   return height;
}

void Component::setPreferredSize(RDimension dim)
{
   RDimension old;
   
   if(prefSet)
      old = prefer;
   else 
      old = nullref;
    
   prefer = dim;
   prefSet = (prefer != nullref);
   firePropertyChanged("preferredSize", old, prefer);
}

vbool Component::isPreferredSizeSet()
{
   return prefSet;
}

RDimension Component::getPreferredSize()
{
   RDimension dim = prefer;
   
   if(dim == nullref || !(isPreferredSizeSet() || isValid()))
   {
      sync_lock(getTreeLock())
      {
         prefer = getMinimumSize();
         
         dim = prefer;
      }
   }
   
   return new Dimension(dim);
}

void Component::setMinimumSize(RDimension dim)
{
   RDimension old;
   
   if(minSet)
      old = min;
   else
      old = nullref;
   
   min = dim;
   minSet = (min != nullref);
   firePropertyChanged("minimumSize", old, min);
}

vbool Component::isMinimumSizeSet()
{
   return minSet;
}

RDimension Component::getMinimumSize()
{
   RDimension dim = min;
   
   if(dim == nullref || !(isMinimumSizeSet() || isValid()))
   {
      sync_lock(getTreeLock())
      {
         min = getSize();
         
         dim = min;
      }
   }
   
   return new Dimension(dim);
}

void Component::setMaximumSize(RDimension dim)
{
   RDimension old;
   
   if(maxSet)
      old = max;
   else
      old = nullref;
   
   max = dim;
   maxSet = (max != nullref);
   firePropertyChanged("maximumSize", old, max);
}

vbool Component::isMaximumSizeSet()
{
   return maxSet;
}

RDimension Component::getMaximumSize()
{
   if(isMaximumSizeSet())
      return new Dimension(max);
   
   //TODO: Determine the max size of component:
   //      1. based on parent, if in a container, or
   //      2. based on size graphical user interface.
   return new Dimension(80, 40);
}

void Component::validate()
{
   if(!valid)
      valid = true;
}

void Component::invalidate()
{
   if(valid)
   {
      sync_lock(getTreeLock())
      {
         valid = false;
         
         if(!isPreferredSizeSet())
            prefer = nullref;
         
         if(!isMinimumSizeSet())
            min = nullref;
         
         if(!isMaximumSizeSet())
            max = nullref;
         
         if(parent != nullref && parent->valid)
            parent->invalidate();
      }
   }
}

//void Component::paint(RGraphics g)
//{
//   
//}

void Component::update(RGraphics g)
{
   g->clear();

   if(isShowing())
      paint(g);
}

void Component::paintAll(RGraphics g)
{
   if(isShowing())
   {
      validate();

      paint(g);
   }
}

vbool Component::isFocusable()
{
   return focusable;
}

void Component::setFocusable(vbool b)
{
   RBool old = Bool::valueOf(focusable); focusable = b;
   
   firePropertyChanged("focusable", old, Bool::valueOf(b));
   
   if(old->boolValue() && !focusable)
   {
      if(isFocusOwner())
         autoTransferFocus(true);
      
      FocusManager::clearMostRecentFocusOwner(thisref);
   }
}

vbool Component::isDisplayable()
{
   return true; // default; may be overridden
}

vbool Component::canBeFocusOwner()
{
   // It is enabled, visible, focusable.
   if(isEnabled() && isDisplayable() && isVisible() && isFocusable())
      return true;
   
   return false;
}

vbool Component::canBeFocusOwner(RComponent comp)
{
   return comp->canBeFocusOwner();
}

void Component::requestFocus()
{
   requestFocusHelper(false, true, FocusCausedEvent::Cause::UNKNOWN);
}

vbool Component::requestFocusInWindow()
{
   return requestFocusHelper(false, false, FocusCausedEvent::Cause::UNKNOWN);
}

vbool Component::requestFocus(vbool temp)
{
   return requestFocusHelper(temp, true, FocusCausedEvent::Cause::UNKNOWN);
}

vbool Component::requestFocusInWindow(vbool temp)
{
   return requestFocusHelper(temp, false, FocusCausedEvent::Cause::UNKNOWN);
}

vbool Component::requestFocus(FocusCausedEvent::RCause cause)
{
   return requestFocusHelper(false, true, cause);
}

vbool Component::requestFocusInWindow(FocusCausedEvent::RCause cause)
{
   return requestFocusHelper(false, false, cause);
}

vbool Component::requestFocus(vbool temp, FocusCausedEvent::RCause cause)
{
   return requestFocusHelper(temp, true, cause);
}

vbool Component::requestFocusInWindow(vbool temp, FocusCausedEvent::RCause cause)
{
   return requestFocusHelper(temp, false, cause);
}

vbool Component::isRequestFocusAccepted(vbool temp, vbool change,
                                       FocusCausedEvent::RCause cause)
{
   if(!isFocusable() || !isVisible())
      return false; // Not focusable or not visible
   
   RWindow window = getParentWindow();
   if(window == nullref || !window->isFocusableWindow())
      return false; // Component doesn't have toplevel
   
   return true;
   // Since the default RequestFocusController always returns true
   // we can pretty much bypass all the code below and just return true
   //
   //// We have passed all regular checks for focus request,
   //// now let's call RequestFocusController and see what it says.
   //RComponent focusOwner = FocusManager::getMostRecentFocusOwner(window);
   //if(focusOwner == nullref)
   //{
   //   // sometimes most recent focus owner may be nullref, but focus owner is not
   //   // e.g. we reset most recent focus owner if user removes focus owner
   //   focusOwner = FocusManager::getFocusManager()->getFocusOwner();
   //   if(focusOwner != nullref && getParentWindow(focusOwner) != window)
   //      focusOwner = nullref;
   //}
   //
   //// Controller is supposed to verify focus transfers and for this it
   //// should know both from and to components.  And it shouldn't verify
   //// transfers from when these components are equal.
   //if(focusOwner == thisref || focusOwner == nullref)
   //   return true; // focus owner is nullref or thisref
   //
   //// we shouldn't call RequestFocusController in case we are
   //// in activation.  We do request focus on component which
   //// has got temporary focus lost and then on component which is
   //// most recent focus owner.  But most recent focus owner can be
   //// changed by requestFocusXXX() call only, so this transfer has
   //// been already approved.
   //if(cause == FocusCausedEvent::Cause::ACTIVATION)
   //   return true; // cause is activation
   //
   //// check out RequestFocusController
   //return Component::requestFocusController->acceptRequestFocus(focusOwner,
   //                thisref, temp, change, cause);
}

vbool Component::requestFocusHelper(vbool temp, vbool change,
                                          FocusCausedEvent::RCause cause)
{
   if(!isRequestFocusAccepted(temp, change, cause))
      return false; // requestFocus is not accepted
   
   // Update most-recent map
   FocusManager::setMostRecentFocusOwner(thisref);
   
   RComponent window = thisref;
   while(window != nullref && !type_of<Window>(window))
   {
      if(!window->isVisible())
         return false; // component is recurively invisible
      
      window = window->parent;
   }
   
   //Focus this component
   vlong time = EventQueue::getMostRecentEventTime();

   RFocusManager mngr = FocusManager::getFocusManager();

   return mngr->focusComponent(thisref, temp, change, cause);
   
   //RWindow aWin = mngr->getActiveWindow();
   //RWindow fWin = mngr->getFocusedWindow();
   //RWindow pWin = getParentWindow();
   //RComponent own = mngr->getFocusOwner();
   //
   //if(fWin == pWin) // within focused window (ignore change)
   //{
   //   // execute direct focus transfer
   //   mngr->setFocusOwner(nullref);
   //   mngr->setMainFocusOwner(nullref);
   //   own->fireLostFocus(false, thisref);
   //   
   //   mngr->setFocusOwner(thisref);
   //   mngr->setMainFocusOwner(thisref);
   //   thisref->fireGotFocus(false, own);
   //}
   //else // from outside focused window
   //{
   //   if(change) // if window change allowed
   //   {
   //      if(aWin == pWin) // non-active focus in effect
   //      {
   //         mngr->setFocusOwner(nullref);
   //         own->fireLostFocus(false, thisref);
   //         
   //         mngr->setFocusedWindow(nullref);
   //         fWin->fireWindowEvent(
   //            new WindowEvent(fWin,WindowEvent::WINDOW_LOST_FOCUS, aWin)
   //         );
   //         
   //         mngr->setFocusedWindow(aWin);
   //         aWin->fireWindowEvent(
   //            new WindowEvent(aWin,WindowEvent::WINDOW_GOT_FOCUS, fWin)
   //         );
   //         
   //         mngr->setFocusOwner(thisref);
   //         mngr->setMainFocusOwner(thisref);
   //         thisref->fireGotFocus(false, own);
   //      }
   //      else // pWin != fWin && pWin != aWin (aWin !=||== fWin)
   //      {
   //         mngr->setFocusOwner(nullref);
   //         own->fireLostFocus(false, thisref);
   //         
   //         mngr->setFocusedWindow(nullref);
   //         fWin->fireWindowEvent(
   //            new WindowEvent(fWin,WindowEvent::WINDOW_LOST_FOCUS, pWin)
   //         );
   //         
   //         // only a Frame or a Dialog can be the activeWindow
   //         if(pWin->isTypeOf<Frame>() || pWin->isTypeOf<Dialog>())
   //         {
   //            mngr->setActiveWindow(nullref);
   //            aWin->fireWindowEvent(
   //               new WindowEvent(aWin,WindowEvent::WINDOW_DEACTIVATED, pWin)
   //            );
   //            
   //            mngr->setActiveWindow(pWin);
   //            pWin->fireWindowEvent(
   //               new WindowEvent(pWin,WindowEvent::WINDOW_ACTIVATED, aWin)
   //            );
   //         }
   //         
   //         mngr->setFocusedWindow(pWin);
   //         pWin->fireWindowEvent(
   //            new WindowEvent(pWin,WindowEvent::WINDOW_GOT_FOCUS, fWin)
   //         );
   //         
   //         mngr->setFocusOwner(thisref);
   //         mngr->setMainFocusOwner(thisref);
   //         thisref->fireGotFocus(temp, own);
   //      }
   //   }
   //   else // no window change allowed
   //   {
   //      if(aWin == pWin) // non-active focus in effect
   //      {
   //         // add Focus Request to focus manager's buffer
   //         // which should be executed as soon as pWin
   //         // becomes the focused window
   //      }
   //      else // pWin != fWin && pWin != aWin (aWin !=||== fWin)
   //      {
   //         // add Focus Request to focus manager's buffer
   //         // which should be executed as soon as pWin
   //         // becomes the focused window
   //      }
   //   }
   //}
   //
   //// see java.awt.Component#requestFocusHelper
   //// for expansion details for code section
   //
   //return true; // success
}

void Component::autoTransferFocus(vbool clearOnFailure)
{
   RComponent toTest = FocusManager::getFocusManager()->getFocusOwner();
   
   if(toTest != thisref)
   {
      if(toTest != nullref)
         toTest->autoTransferFocus(clearOnFailure);
      
      return;
   }
   
   // Check if there are pending focus requests.  We shouldn't do
   // auto-transfer if user has already took care of this
   // component becoming ineligible to hold focus.
   if(FocusManager::hasFocusRequests())
      return;
   
   // the following code will execute only if this
   // Component is the focus owner
   if(!(isVisible() && isEnabled() && isFocusable()))
   {
      doAutoTransfer(clearOnFailure);
      return;
   }
   
   toTest = getParent();
   
   while(toTest != nullref && !type_of<Window>(toTest))
   {
      // the actual code transposed from java would be:
      // if(!(isVisible() && (isEnabled() || isLightWeight()))
      // but since all components in the AROLib are light-weight
      // the "OR" condition will always be true
      if(!isVisible())
      {
         doAutoTransfer(clearOnFailure);
         return;
      }
      
      toTest = toTest->getParent();
   }
}

void Component::doAutoTransfer(vbool clearOnFailure)
{
   if(clearOnFailure)
   {
      if(!transferFocusHelper())
         FocusManager::getFocusManager()->setFocusOwner(nullref);
   }
   else
      transferFocus();
}

void Component::transferFocus()
{
   transferFocusHelper();
}

vbool Component::transferFocusHelper()
{
   RWindow root = getParentWindow();
   RComponent toFocus = nullref;
   
   if(root != nullref)
   {
      RFocusPolicy policy = FocusManager::getFocusManager()->getFocusPolicy();
      
      toFocus = policy->getNext(root, thisref);
      
      if(toFocus == nullref)
         toFocus = policy->getDefault(root);
   }
   
   if(isFocusOwner() && toFocus == thisref)
      return false;
   
   if(toFocus != nullref)
      return toFocus->requestFocusHelper(false, false, FocusCausedEvent::Cause::FOCUS_NEXT);
   
   return false;
}

void Component::transferFocusBackward()
{
   RWindow root = getParentWindow();
   
   if(root != nullref)
   {
      RFocusPolicy policy = FocusManager::getFocusManager()->getFocusPolicy();
      
      RComponent toFocus = policy->getPrevious(root, thisref);
      
      if(toFocus == nullref)
         toFocus = policy->getDefault(root);
      
      if(toFocus != nullref)
         toFocus->requestFocusHelper(false, false, FocusCausedEvent::Cause::FOCUS_PREVIOUS);
   }
}

vbool Component::isFocusOwner()
{
   return (FocusManager::getFocusManager()->getFocusOwner() == thisref);
}

vbool Component::isFocused()
{
   return focus;
}

void Component::repaint()
{
   repaint(0, 0, width, height);
}

void Component::repaint(vint x, vint y, vint w, vint h)
{
   if(parent != nullref)
   {
      vint px = thisref->x + (x < 0) ? 0 : x;
      vint py = thisref->y + (y < 0) ? 0 : x;
      vint pwidth = (w > width) ? width : w;
      vint pheight = (h > height) ? height : h;

      parent->repaint(px, py, pwidth, pheight);
   }
   else
   {
      RPaintEvent e = new PaintEvent(thisref,
         PaintEvent::UPDATE, new class Rectangle(x, y, w, h));
      
      System::getEventQueue()->postEvent(e);
   }
}

void Component::revalidate()
{
   valid = false;
   
   if(parent != nullref)
      parent->revalidate();
   else
      validate();
}

vbool Component::isParentWindow(RContainer w)
{
   RContainer root = getParentWindow();
   
   return (root == w);
}

RWindow Component::getParentWindow()
{
   return getParentWindow(thisref);
}

RWindow Component::getParentWindow(RComponent comp)
{
   while(comp != nullref && !type_of<Window>(comp))
      comp = comp->getParent();
   
   return type_cast<Window>(comp);
}

void Component::dispatchEvent(RAWSEvent e)
{
   // 0. Set timestamp and modifiers of current event.
   if(!type_of<KeyEvent>(e))
      EventQueue::setCurrentEventAndMostRecentTime(e);
   
   // 1. Pre-dispatcher. Do any necessary retargeting/reordering here
   //    before we notify AWSEventListeners.
   if(!e->atFocusManager)
   {
      if(e->isPosted)
      {
         // retarget if necessary
         e = FocusManager::retargetFocusEvent(e);
         e->isPosted = true;
      }
      
      // Let focus manager dispatch event
      if(FocusManager::getFocusManager()->dispatchEvent(e))
         return; // focus manager dispatched successfully
   }
   
   // 2. If no one has consumed a key event, allow the
   //    FocusManager to process it.
   if(!e->isConsumed())
   {
      if(type_of<KeyEvent>(e))
      {
         FocusManager::getFocusManager()->processKeyEvent(thisref, type_cast<KeyEvent>(e));
         
         if(e->isConsumed())
            return; // key event was consumed
      }
   }
   
   // 3. Pre-process any special events before delivery
   vint id = e->getEventID();

   if(id == KeyEvent::KEY_PRESSED || id == KeyEvent::KEY_RELEASED)
   {
      RContainer p = type_of<Container>(thisref) ? type_cast<Container>(thisref) : parent;

      if(p != nullref)
      {
         p->preProcessKeyEvent(type_cast<KeyEvent>(e));

         if(e->isConsumed())
            return;
      }
   }
   else if (id == PaintEvent::PAINT || id == PaintEvent::UPDATE)
   {
      e->consume();

      // NOTE: might be prudent to intercept paint event from the
      //       event queue and execute it at that processing level.
      
      RGraphics g = System::getGraphics(type_cast<PaintEvent>(e));
      
      if(isVisible() && (width > 0) && (height > 0))
      {
         if(id == PaintEvent::PAINT)
            paint(g);
         
         else //if(id == PaintEvent::UPDATE)
            update(g);
      }
      else
         g->clear();
      
      return;
   }
   
   // 4. Deliver event for normal processing
   processEvent(e);
}

void Component::processEvent(RAWSEvent e)
{
   if(type_of<KeyEvent>(e))
   {
      processKeyEvent(type_cast<KeyEvent>(e));
   }
   else if(type_of<FocusEvent>(e))
   {
      processFocusEvent(type_cast<FocusEvent>(e));
   }
   else if(type_of<ComponentEvent>(e))
   {
      processComponentEvent(type_cast<ComponentEvent>(e));
   }
}

void Component::processKeyEvent(RKeyEvent e)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   vint id = e->getEventID();
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<KeyListener>(arr[n]))
      {
         RKeyListener rkl = type_cast<KeyListener>(arr[n]);
         
         if(id == KeyEvent::KEY_TYPED)
            rkl->keyTyped(e);
         else if(id == KeyEvent::KEY_PRESSED)
            rkl->keyPressed(e);
         else if(id == KeyEvent::KEY_RELEASED)
            rkl->keyRealeased(e);
      }
   }
}

void Component::processFocusEvent(RFocusEvent e)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   vint id = e->getEventID();
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<FocusListener>(arr[n]))
      {
         RFocusListener rfl = type_cast<FocusListener>(arr[n]);
         
         if(id == FocusEvent::GOT_FOCUS)
            rfl->gotFocus(e);
         else if(id == FocusEvent::LOST_FOCUS)
            rfl->lostFocus(e);
      }
   }
}

void Component::processComponentEvent(RComponentEvent e)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   vint id = e->getEventID();
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<ComponentListener>(arr[n]))
      {
         RComponentListener rcl = type_cast<ComponentListener>(arr[n]);
         
         if(id == ComponentEvent::COMPONENT_MOVED)
            rcl->componentMoved(e);
         else if(id == ComponentEvent::COMPONENT_SHOWN)
            rcl->componentShown(e);
         else if(id == ComponentEvent::COMPONENT_HIDDEN)
            rcl->componentHidden(e);
         else if(id == ComponentEvent::COMPONENT_RESIZED)
            rcl->componentResized(e);
      }
   }
}

void Component::addKeyListener(RKeyListener l)
{
   listeners->add<KeyListener>(l);
}

RArray<KeyListener> Component::getKeyListeners()
{
   return listeners->getListeners<KeyListener>();
}

void Component::removeKeyListener(RKeyListener l)
{
   listeners->remove<KeyListener>(l);
}

RArray<FocusListener> Component::getFocusListeners()
{
   return listeners->getListeners<FocusListener>();
}

void Component::addFocusListener(RFocusListener l)
{
   listeners->add<FocusListener>(l);
}

void Component::removeFocusListener(RFocusListener l)
{
   listeners->remove<FocusListener>(l);
}

RArray<PropertyListener> Component::getPropertyListeners()
{
   return listeners->getListeners<PropertyListener>();
}

void Component::addPropertyListener(RPropertyListener l)
{
   listeners->add<PropertyListener>(l);
}

void Component::removePropertyListener(RPropertyListener l)
{
   listeners->remove<PropertyListener>(l);
}

RArray<ComponentListener> Component::getComponentListeners()
{
   return listeners->getListeners<ComponentListener>();
}

void Component::addComponentListener(RComponentListener l)
{
   listeners->add<ComponentListener>(l);
}

void Component::removeComponentListener(RComponentListener l)
{
   listeners->remove<ComponentListener>(l);
}

void Component::firePropertyChanged(RString name,
                                         RObject oldVal, RObject newVal)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   RPropertyEvent e = new PropertyEvent(thisref,
                      PropertyEvent::PROPERTY_CHANGED, name, oldVal, newVal);
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<PropertyListener>(arr[n]))
      {
         RPropertyListener rpl = type_cast<PropertyListener>(arr[n]);
         
         rpl->propertyChanged(e);
      }
   }
}

} /* namespace aws */

} /* namespace aro */
