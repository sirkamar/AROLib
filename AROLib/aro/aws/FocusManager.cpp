#include <aro/core.hpp>
#include <aro/aws/Frame.hpp>
#include <aro/aws/Dialog.hpp>
#include <aro/aws/KeyStroke.hpp>
#include <aro/util/ArrayList.hpp>
#include <aro/aws/FocusManager.hpp>
#include <aro/util/WeakHashMap.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/aws/DefaultFocusPolicy.hpp>
#include <aro/aws/DefaultFocusManager.hpp>
#include <aro/aws/event/PropertyEvent.hpp>
#include <aro/aws/event/FocusCausedEvent.hpp>

namespace aro {

namespace aws {

using namespace util;
using namespace event;

const vint FocusManager::FOCUS_NEXT_KEYS = 0;
const vint FocusManager::FOCUS_PREV_KEYS = 1;

RWindow FocusManager::activeWindow;
RWindow FocusManager::focusedWindow;
RComponent FocusManager::focusOwner;
RFocusManager FocusManager::manager;
RComponent FocusManager::newFocusOwner;
RComponent FocusManager::permanentFocusOwner;
RContainer FocusManager::currentFocusCycleRoot;

const RObject FocusManager::CLASS_LOCK = new Object();

FocusManager::RFocusRequest FocusManager::currentRequest;
RLinkedList<FocusManager::FocusRequest> FocusManager::focusRequests;

const RArray2D<KeyStroke> FocusManager::defaultFocusTraversalKeys = {
   //The "Next" focus traversal keys
   {
      KeyStroke::getKeyStroke(KeyEvent::VKEY_TAB, 0, false), //TAB Key
      KeyStroke::getKeyStroke(KeyEvent::VKEY_TAB, KeyEvent::CTRL_MASK, false) //CTRL+TAB
   },
   //The "Previous" focus traversal keys
   {
      KeyStroke::getKeyStroke(KeyEvent::VKEY_TAB, KeyEvent::SHIFT_MASK, false), //SHIFT+TAB
      KeyStroke::getKeyStroke(KeyEvent::VKEY_TAB, KeyEvent::SHIFT_MASK|KeyEvent::CTRL_MASK, false) //CTRL+SHIFT+TAB
   }
};

RMap<Window, Weak<Component>> FocusManager::mostRecentFocusOwners = new WeakHashMap<Window, Weak<Component>>();

FocusManager::FocusManager()
{
   listeners = new ListenerList();
   policy = new DefaultFocusPolicy();
   
   focusTraversalKeys = new Array<List<KeyStroke>>(2);
   
   for(int n=0; n<defaultFocusTraversalKeys->length; n++)
   {
      focusTraversalKeys[n] = new ArrayList<KeyStroke>(2);
      
      for(int m=0; m<defaultFocusTraversalKeys[n]->length; m++)
         focusTraversalKeys[n]->add(defaultFocusTraversalKeys[n][m]);
   }
   
   //TODO: figure out how focusRequests list is used
   //focusRequests = new LinkedList<FocusManager::FocusRequest>();
}

void FocusManager::clearFocusOwner()
{
   markClearFocusOwner();
}

RWindow FocusManager::getActiveWindow()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      return activeWindow;
   }
}

RWindow FocusManager::getFocusedWindow()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      return focusedWindow;
   }
}

RComponent FocusManager::getFocusOwner()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      return focusOwner;
   }
}

void FocusManager::focusNextComponent()
{
   RComponent current = getFocusOwner();
   
   if(current != nullref)
      focusNextComponent(current);
}

void FocusManager::focusPreviousComponent()
{
   RComponent current = getFocusOwner();
   
   if(current != nullref)
      focusPreviousComponent(current);
}

RFocusPolicy FocusManager::getFocusPolicy()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      return policy;
   }
}

RComponent FocusManager::getPermanentFocusOwner()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      return permanentFocusOwner;
   }
}

RFocusManager FocusManager::getFocusManager()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      if(manager == nullref)
         manager = new DefaultFocusManager();
      
      return manager;
   }
}

RContainer FocusManager::getCurrentFocusCycleRoot()
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      return currentFocusCycleRoot;
   }
}

RList<KeyStroke> FocusManager::getFocusTraversalKeys(vint id)
{
   if(id == FOCUS_NEXT_KEYS || id == FOCUS_PREV_KEYS)
      return focusTraversalKeys[id];
   
   return new ArrayList<KeyStroke>(0);
}

void FocusManager::setActiveWindow(RWindow win)
{
   RWindow oldActiveWindow;

   sync_lock(FocusManager::CLASS_LOCK)
   {
      oldActiveWindow = activeWindow;

      activeWindow = win;
   }

   firePropertyChanged("activeWindow", oldActiveWindow, win);
}

void FocusManager::setFocusedWindow(RWindow win)
{
   if(win == nullref || win->isFocusableWindow())
   {
      RWindow oldFocusedWindow;
      
      sync_lock(FocusManager::CLASS_LOCK)
      {
         oldFocusedWindow = focusedWindow;

         focusedWindow = win;
      }

      firePropertyChanged("focusedWindow", oldFocusedWindow, win);
   }
}

void FocusManager::setFocusOwner(RComponent comp)
{
   if(comp == nullref || comp->isFocusable())
   {
      RComponent oldFocusOwner;

      sync_lock(FocusManager::CLASS_LOCK)
      {
         oldFocusOwner = focusOwner;
         
         focusOwner = comp;
         
         RContainer root = getCurrentFocusCycleRoot();
         
         if(focusOwner != nullref && (root == nullref || !focusOwner->isParentWindow(root)))
         {
            root = focusOwner->getParentWindow();

            if(root == nullref && type_of<Window>(focusOwner))
               root = type_cast<Container>(focusOwner);

            if(root != nullref)
               setCurrentFocusCycleRoot(root);
         }

         if(root != nullref)
            root->repaint();
      }

      firePropertyChanged("focusOwner", oldFocusOwner, comp);
   }
}

void FocusManager::setPermanentFocusOwner(RComponent comp)
{
   if(comp == nullref || comp->isFocusable())
   {
      RComponent oldPermFocusOwner;

      sync_lock(FocusManager::CLASS_LOCK)
      {
         oldPermFocusOwner = permanentFocusOwner;

         permanentFocusOwner = comp;

         setMostRecentFocusOwner(comp);
      }

      firePropertyChanged("permanentFocusOwner", oldPermFocusOwner, comp);
   }
}

void FocusManager::setFocusPolicy(RFocusPolicy newPolicy)
{
   if(newPolicy == nullref)
      ex_throw new ArgumentException("focus policy cannot be null");
   
   RFocusPolicy oldPolicy;

   sync_lock(FocusManager::CLASS_LOCK)
   {
      oldPolicy = policy;
      policy = newPolicy;
   }

   firePropertyChanged("focusPolicy", oldPolicy, newPolicy);
}

void FocusManager::setFocusManager(RFocusManager mngr)
{
   RFocusManager oldManager;
   
   sync_lock(FocusManager::CLASS_LOCK)
   {
      oldManager = manager;
      manager = mngr;
   }
   
   if(oldManager != nullref)
      oldManager->firePropertyChanged("focusManager", Bool::IS_TRUE, Bool::IS_FALSE);
   
   if(mngr != nullref)
      mngr->firePropertyChanged("focusManager", Bool::IS_FALSE, Bool::IS_TRUE);
}

void FocusManager::setCurrentFocusCycleRoot(RContainer root)
{
   RContainer oldFocusCycleRoot;

   sync_lock(FocusManager::CLASS_LOCK)
   {
      oldFocusCycleRoot = currentFocusCycleRoot;

      currentFocusCycleRoot = root;
   }

   firePropertyChanged("currentFocusCycleRoot", oldFocusCycleRoot, root);
}

void FocusManager::setFocusTraversalKeys(vint id, RList<KeyStroke> keyStrokes)
{
   //TODO: update to fully validate traversal key strokes
   if(id == FOCUS_NEXT_KEYS || id == FOCUS_PREV_KEYS)
      focusTraversalKeys[id] = keyStrokes;
   
   //firePropertyChanged("focusTraversalKeys", oldKeyStrokes, keyStrokes);
}

void FocusManager::addPropertyListener(RPropertyListener l)
{
   listeners->add<PropertyListener>(l);
}

void FocusManager::removePropertyListener(RPropertyListener l)
{
   listeners->remove<PropertyListener>(l);
}

RArray<PropertyListener> FocusManager::getPropertyListeners()
{
   return listeners->getListeners<PropertyListener>();
}

void FocusManager::firePropertyChanged(RString name,
                                         RObject oldVal, RObject newVal)
{
   RArray<Listener> arr = listeners->getListeners();
   
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

void FocusManager::setMostRecentFocusOwner(RComponent comp)
{
   RComponent window = comp;

   while(window != nullref && !type_of<Window>(window))
      window = window->getParent();
   
   if(window != nullref)
      setMostRecentFocusOwner(type_cast<Window>(window), comp);
}

void FocusManager::clearMostRecentFocusOwner(RComponent comp)
{
   RContainer window;
   
   if(comp == nullref)
      return;
   
   sync_lock(comp->getTreeLock())
   {
      window = comp->getParent();
      while(window != nullref && !type_of<Window>(window))
         window = window->getParent();
   }
   
   sync_lock(FocusManager::CLASS_LOCK)
   {
      if(window != nullref && getMostRecentFocusOwner(type_cast<Window>(window)) == comp)
         setMostRecentFocusOwner(type_cast<Window>(window), nullref);
      
      // also clear temporary lost component stored in Window
      if(window != nullref)
      {
         RWindow realWindow = type_cast<Window>(window);

         if(realWindow->getTemporaryLostComponent() == comp)
            realWindow->setTemporaryLostComponent(nullref);
      }
   }
}

RComponent FocusManager::getMostRecentFocusOwner(RWindow win)
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      RWeak<Component> value = mostRecentFocusOwners->get(win);
      
      return value == nullref ? nullref : value->get();
   }
}

void FocusManager::setMostRecentFocusOwner(RWindow win, RComponent comp)
{
   sync_lock(FocusManager::CLASS_LOCK)
   {
      // ATTN: component has a strong reference to window via chain
      // of Component->parent fields.  Since WeakHashMap refers to its
      // values strongly, we need to break the strong link from the
      // value (component) back to its key (window).
      RWeak<Component> value;
      
      if(comp != nullref)
         value = new Weak<Component>(comp);
      
      mostRecentFocusOwners->put(win, value);
   }
}

//This function is in lieu of Component::peer->requestFocus()
vbool FocusManager::focusComponent(RComponent target, vbool temp,
                   vbool changeAllowed, FocusCausedEvent::RCause cause)
{
   RComponent own, aWin, fWin, pWin;

   sync_lock(FocusManager::CLASS_LOCK)
   {
      own = getFocusOwner();
      aWin = getActiveWindow();
      fWin = getFocusedWindow();
      pWin = target->getParentWindow();
   }

   if(fWin == pWin || changeAllowed)
   {
      RFocusEvent fe;
      


      if(cause == FocusCausedEvent::Cause::UNKNOWN)
         fe = new FocusEvent(target,FocusEvent::GOT_FOCUS,temp,own);
      else
         fe = new FocusCausedEvent(target,FocusEvent::GOT_FOCUS,temp,own,cause);
      
      dispatchEvent(fe);
   }
   else
   {
      // save request for later
   }
   
   return true;
}

void FocusManager::redispatchEvent(RComponent c, RAWSEvent e)
{
   e->atFocusManager = true;
   
   c->dispatchEvent(e);
   
   e->atFocusManager = false;
}

RAWSEvent FocusManager::retargetFocusEvent(RAWSEvent e)
{
   if(clearingCurrent)
      return e;
   
   RFocusManager manager = FocusManager::getFocusManager();
   
   if(newFocusOwner != nullref && e->getEventID() == FocusEvent::LOST_FOCUS)
   {
      RFocusEvent fe = type_cast<FocusEvent>(e);
      
      if(manager->getFocusOwner() == fe->getComponent() && fe->getOtherComponent() == newFocusOwner)
      {
         newFocusOwner = nullref;
         
         return e;
      }
   }
   
   processCurrentRequests();
   
   switch(e->getEventID())
   {
      case FocusEvent::GOT_FOCUS:
         e = retargetGotFocus(type_cast<FocusEvent>(e));
         break;
      
      case FocusEvent::LOST_FOCUS:
         e = retargetLostFocus(type_cast<FocusEvent>(e));
         break;
      
      default:
         ;// do nothing
   }

   return e;
}

RFocusEvent FocusManager::retargetGotFocus(RFocusEvent fe)
{
   //assert (fe->getID() == FocusEvent::GOT_FOCUS);
   
   RComponent currentFocusOwner = getFocusManager()->getFocusOwner();
   RComponent source = fe->getComponent();
   RComponent other = fe->getOtherComponent();

   if(currentFocusOwner != nullref && currentFocusOwner->getParentWindow() == source)
      return new FocusCausedEvent(currentFocusOwner, FocusEvent::GOT_FOCUS,
               false, nullref, FocusCausedEvent::Cause::ACTIVATION);
   
   return retargetUnexpectedFocusEvent(fe);
}

RFocusEvent FocusManager::retargetLostFocus(RFocusEvent fe)
{
   //assert (fe->getID() == FocusEvent::LOST_FOCUS);
   
   RComponent currentFocusOwner = getFocusManager()->getFocusOwner();
   RComponent other = fe->getOtherComponent();
   
   if(other == nullref)
   {
      if(currentFocusOwner != nullref)
      {
         return new FocusCausedEvent(currentFocusOwner, FocusEvent::LOST_FOCUS,
                           true, nullref, FocusCausedEvent::Cause::ACTIVATION);
      }
      else
      {
         return fe;
      }
   }
   else if(focusedWindowChanged(other, currentFocusOwner))
   {
      if(!fe->isTemporary() && currentFocusOwner != nullref)
      {
         fe = new FocusCausedEvent(currentFocusOwner, FocusEvent::LOST_FOCUS,
                        true, other, FocusCausedEvent::Cause::ACTIVATION);
      }

      return fe;
   }

   return retargetUnexpectedFocusEvent(fe);
}

RFocusEvent FocusManager::retargetUnexpectedFocusEvent(RFocusEvent fe)
{
   if(removeFirstRequest())
      return type_cast<FocusEvent>(retargetFocusEvent(fe));
   
   vbool temporary = false;
   RComponent source = fe->getComponent();
   RComponent other = fe->getOtherComponent();
   
   if(fe->getEventID() == FocusEvent::LOST_FOCUS && (other == nullref || isTemporary(other, source)))
      temporary = true;
   
   return new FocusCausedEvent(source, fe->getEventID(), temporary, other, FocusCausedEvent::Cause::NATIVE_SYSTEM);
}

vbool FocusManager::focusedWindowChanged(RComponent from, RComponent to)
{
   RWindow wfrom = from->getParentWindow();
   RWindow wto = to->getParentWindow();
    
   if(wfrom == nullref || wto == nullref)
      return true;
   
   return (wfrom != wto);
}

const FocusManager::RFocusRequest
   FocusManager::FocusRequest::CLEAR_FOCUS_OWNER = new FocusManager::FocusRequest();

FocusManager::FocusRequest::FocusRequest(RComponent cmp, vbool temp,
                                         FocusCausedEvent::RCause cauze)
   :comp(cmp), temporary(temp), cause(cauze)
{
   
}

FocusManager::FocusRequest::FocusRequest()
   :temporary(false), cause(FocusCausedEvent::Cause::UNKNOWN)
{
   
}

vbool FocusManager::disableRestore = false;
vbool FocusManager::clearingCurrent = false;
vbool FocusManager::allowSyncRequests = false;

RWindow FocusManager::markClearFocusOwner()
{
   sync_lock(focusRequests)
   {
	   RFocusRequest focusRequest;
	   if(focusRequests->size() > 0)
		   focusRequest = focusRequests->getLast();
	   
	   if(focusRequest == FocusRequest::CLEAR_FOCUS_OWNER)
		  return nullref;
	   
	   RFocusManager mngr = getFocusManager();
	   focusRequests->add(FocusRequest::CLEAR_FOCUS_OWNER);
	   
	   RComponent activeWindow;
	   if(focusRequest != nullref)
		  activeWindow = Component::getParentWindow(focusRequest->comp);
	   else
		  activeWindow = mngr->getFocusedWindow();
	   
	   while(activeWindow != nullref &&
         !(type_of<Frame>(activeWindow) || type_of<Dialog>(activeWindow)))
		  activeWindow = activeWindow->getParent();
      
	   return type_cast<Window>(activeWindow);
   }
}

RComponent FocusManager::getFocusRequest(RComponent parent)
{
   sync_lock(focusRequests)
   {
	   RFocusRequest focusRequest;
	   if(focusRequests->size() > 0)
		  focusRequest = focusRequests->getLast();
	   
	   if(focusRequest != nullref)
	   {
		  return focusRequest->comp;
		  /*if(focusRequest->comp == parent)
		  {
	         
		  }*/
	   }
   }
   
   return nullref;
}

vbool FocusManager::hasFocusRequests()
{
   sync_lock(focusRequests)
   {
      return focusRequests->size() > 0;
   }
}

void FocusManager::processCurrentRequests()
{
   RFocusManager mngr = getFocusManager();
   RLinkedList<FocusRequest> localRequests = nullref;
   
   //sync_lock(focusRequests)
   //{
      if(focusRequests != nullref)
	   {
		  disableRestore = true;
		  clearingCurrent = true;
		  localRequests = focusRequests;
		  allowSyncRequests = (localRequests->size() < 2);
		  focusRequests = nullref;
	   }
	   else
	   {
		  // do nothing
		  return;
	   }
   //}

   if(localRequests != nullref)
   {
      RComponent lastFocusOwner = nullref;
      RComponent currentFocusOwner = nullref;

      for(RIterator<FocusRequest> iter = localRequests->iterator(); iter->hasNext();)
      {
         currentFocusOwner = mngr->getFocusOwner();

         RFocusRequest lFocusRequest = iter->next();

         if(!iter->hasNext())
            disableRestore = false;
         
         RFocusEvent currentFocusOwnerEvent = nullref;
         
         ex_try
         {
            if(currentFocusOwner != nullref)
               currentFocusOwnerEvent = new FocusCausedEvent(currentFocusOwner,
                        FocusEvent::LOST_FOCUS, lFocusRequest->temporary,
                        lFocusRequest->comp, lFocusRequest->cause);
            
            RFocusEvent newFocusOwnerEvent = new FocusCausedEvent(lFocusRequest->comp,
                        FocusEvent::GOT_FOCUS, lFocusRequest->temporary,
                        currentFocusOwner == nullref ? lastFocusOwner :
                        currentFocusOwner, lFocusRequest->cause);
            
            if(currentFocusOwner != nullref)
            {
               currentFocusOwnerEvent->isPosted = true;

               ex_try
               {
                  currentFocusOwner->dispatchEvent(currentFocusOwnerEvent);
               }
               ex_catch
               {
                  ex_handle(Exception)
                  {
                     ex_var->printException();
                  }
               }
               ex_end
            }
            
            newFocusOwnerEvent->isPosted = true;
            
            ex_try
            {
               lFocusRequest->comp->dispatchEvent(newFocusOwnerEvent);
            }
            ex_catch
            {
               ex_handle(Exception)
               {
                  ex_var->printException();
               }
            }
            ex_end
            
            if(mngr->getFocusOwner() == lFocusRequest->comp)
               lastFocusOwner = lFocusRequest->comp;
         }
         ex_catch
         {
            ex_finally
            {
               clearingCurrent = true;
               disableRestore = false;
               localRequests = nullref;
               allowSyncRequests = true;
            }
         }
         ex_end
      }
   }
}

vbool FocusManager::isTemporary(RComponent to, RComponent from)
{
   RWindow wto = to->getParentWindow();
   RWindow wfrom = from->getParentWindow();
   
   if(wto == nullref && wfrom == nullref)
      return false;
   
   if(wto == nullref)
      return true;
   
   if(wfrom == wfrom)
      return false;
   
   return (wto == wfrom);
}

vbool FocusManager::removeFirstRequest()
{
   //TODO: figure out usage or remove
   //focusRequests->removeFirst();
   //
   //return focusRequests->size() > 0;
   
   return false;
}

} /* namespace aws */

} /* namespace aro */
