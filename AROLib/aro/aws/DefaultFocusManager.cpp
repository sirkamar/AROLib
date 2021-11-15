#include <aro/core.hpp>
#include <aro/aws/Frame.hpp>
#include <aro/aws/Dialog.hpp>
#include <aro/aws/KeyStroke.hpp>
#include <aro/util/LinkedList.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/aws/event/WindowEvent.hpp>
#include <aro/aws/DefaultFocusManager.hpp>
#include <aro/aws/event/FocusCausedEvent.hpp>
#include <aro/aws/event/FocusCausedEvent.hpp>

namespace aro {

namespace aws {

using namespace util;
using namespace event;

const RWeak<Window> DefaultFocusManager::NULL_WINDOW_WR = new Weak<Window>(nullref);

const RWeak<Component> DefaultFocusManager::NULL_COMPONENT_WR = new Weak<Component>(nullref);

DefaultFocusManager::DefaultFocusManager()
{
   inSendMessage = 0;
   consumeNextTypedKey = false;
   realOppositeWindow = NULL_WINDOW_WR;
   realOppositeComponent = NULL_COMPONENT_WR;
   enqueuedKeyEvents = new LinkedList<KeyEvent>();
   typeAheadMarkers = new LinkedList<TypeAheadMarker>();
}

vbool DefaultFocusManager::dispatchEvent(RAWSEvent e)
{
   switch(e->getEventID())
   {
      case WindowEvent::WINDOW_GOT_FOCUS:
      {
         RWindowEvent we = type_cast<WindowEvent>(e);
         RWindow oldFocusedWindow = getFocusedWindow();
         RWindow newFocusedWindow = we->getWindow();
      
         if(oldFocusedWindow == newFocusedWindow)
            break;
         
         // If there exists a current focused window,
         // then notify it that it has lost focus.
         if(oldFocusedWindow != nullref)
         {
            vbool isDispatched = sendMessage(oldFocusedWindow,
                        new WindowEvent(oldFocusedWindow,
                              WindowEvent::WINDOW_LOST_FOCUS,
                              newFocusedWindow));
            
            // Failed to dispatch, clear by ourselves
            if(!isDispatched)
            {
               setFocusOwner(nullref);
               setFocusedWindow(nullref);
            }
         }
         
         // Because the system doesn't natively post WINDOW_ACTIVATED
         // events, we must synthesize one if the active Window changed.
         RWindow newActiveWindow = getOwningFrameDialog(newFocusedWindow);
         RWindow currentActiveWindow = getActiveWindow();
         if(newActiveWindow != currentActiveWindow)
         {
            sendMessage(newActiveWindow,
               new WindowEvent(newActiveWindow,
                  WindowEvent::WINDOW_ACTIVATED,
                  currentActiveWindow));
            
            if(newActiveWindow != getActiveWindow())
            {
               restoreFocus(we);
               break;
            }
         }
         
         setFocusedWindow(newFocusedWindow);
         
         if(newFocusedWindow != getFocusedWindow())
         {
            // restore focus here
            restoreFocus(we);
            break;
         }
         
         if(inSendMessage == 0)
         {
            RComponent toFocus = FocusManager::
                           getMostRecentFocusOwner(newFocusedWindow);
            if(toFocus != nullref && newFocusedWindow->isFocusableWindow())
            {
               toFocus = FocusManager::getFocusManager()->getFocusPolicy()->getDefault(newFocusedWindow);
            }
            
            RComponent tempLost = newFocusedWindow->setTemporaryLostComponent(nullref);
            
            if(tempLost != nullref)
               tempLost->requestFocusInWindow(FocusCausedEvent::Cause::ACTIVATION);
         
            if(toFocus != nullref && toFocus != tempLost)
               toFocus->requestFocusInWindow(FocusCausedEvent::Cause::ACTIVATION);
         }
         
         RWindow realOppositeWindow = thisref->realOppositeWindow->get();
         if(realOppositeWindow != we->getOtherWindow())
         {
            we = new WindowEvent(newFocusedWindow,
                        WindowEvent::WINDOW_GOT_FOCUS,
                        realOppositeWindow);
         }
         
         return typeAheadAssertions(newFocusedWindow, we);
      }
      
      case WindowEvent::WINDOW_ACTIVATED:
      {
         RWindowEvent we = type_cast<WindowEvent>(e);
         RWindow oldActiveWindow = getActiveWindow();
         RWindow newActiveWindow = we->getWindow();
         
         if(oldActiveWindow == newActiveWindow)
            return true;
         
         // If there exists a current active window,
         // then notify it that it has lost activation.
         if(oldActiveWindow != nullref)
         {
            vbool isDispatched = sendMessage(oldActiveWindow,
                        new WindowEvent(oldActiveWindow,
                              WindowEvent::WINDOW_DEACTIVATED,
                              newActiveWindow));
            
            // Failed to dispatch, clear by ourselves
            if(!isDispatched)
               setActiveWindow(nullref);
            
            if(getActiveWindow() != nullref)
            {
               // Activation change was rejected.
               // Unlikely, but possible.
               return true;
            }
         }
         
         setActiveWindow(newActiveWindow);
         
         if(newActiveWindow != getActiveWindow())
         {
            // Activation change was rejected.
            // Unlikely, but possible.
            return true;
         }
         
         return typeAheadAssertions(newActiveWindow, we);
      }
      
      case FocusEvent::GOT_FOCUS:
      {
         RFocusEvent fe = type_cast<FocusEvent>(e);
         FocusCausedEvent::RCause cause = type_of<FocusCausedEvent>(fe) ?
            type_cast<FocusCausedEvent>(fe)->getCause() : FocusCausedEvent::Cause::UNKNOWN;
         RComponent oldFocusOwner = getFocusOwner();
         RComponent newFocusOwner = fe->getComponent();
         
         if(oldFocusOwner == newFocusOwner)
         {
            // We can't just drop the event - there could be
            // type-ahead markers associated with it.
            dequeueKeyEvents(-1, newFocusOwner);
            return true;
         }
         
         // If there exists a current focus owner,
         // then notify it that it has lost focus.
         if(oldFocusOwner != nullref)
         {
            vbool isDispatched = sendMessage(oldFocusOwner,
                        new FocusCausedEvent(oldFocusOwner,
                                             FocusEvent::LOST_FOCUS,
                                             fe->isTemporary(),
                                             newFocusOwner,
                                             cause));
            
            // Failed to dispatch, clear by ourselfves
            if(!isDispatched)
            {
               setFocusOwner(nullref);
               if(!fe->isTemporary())
                  setPermanentFocusOwner(nullref);
            }
         }
         
         // The native windowing system has a different notion
         // of the current focus and activation states, it is
         // possible that a Component outside of the focused
         // Window receives a GOT_FOCUS event. We synthesize
         // a WINDOW_GOT_FOCUS event in that case.
         RComponent newFocusedWindow = newFocusOwner;
         while(newFocusedWindow != nullref &&
            !type_of<Window>(newFocusedWindow))
            newFocusedWindow = newFocusedWindow->getParent();
         
         RWindow currentFocusedWindow = getFocusedWindow();
         if(newFocusedWindow != nullref &&
               newFocusedWindow != currentFocusedWindow)
         {
            sendMessage(newFocusedWindow,
                     new WindowEvent(type_cast<Window>(newFocusedWindow),
                              WindowEvent::WINDOW_GOT_FOCUS,
                              currentFocusedWindow));
            
            if(newFocusedWindow != getFocusedWindow())
            {
               // Focus change was rejected. Will happen if
               // newFocusedWindow is not a focusable Window.

               // Need to recover type-ahead, but don't bother
               // restoring focus. That was done by the
               // WINDOW_GOT_FOCUS handler
               dequeueKeyEvents(-1, newFocusOwner);
               return true;
            }
         }
         
         setFocusOwner(newFocusOwner);
         
         if(newFocusOwner != getFocusOwner())
         {
            // Focus change rejectd. Will happen if
            // newFocusOwner is not focusable
            dequeueKeyEvents(-1, newFocusOwner);
            if(!disableRestore)
               restoreFocus(fe, type_cast<Window>(newFocusedWindow));
            
            return true;
         }
         
         if(!fe->isTemporary())
         {
            setPermanentFocusOwner(newFocusOwner);
            
            if(newFocusOwner != getPermanentFocusOwner())
            {
               // Focus change rejected.
               dequeueKeyEvents(-1, newFocusOwner);
               if(!disableRestore) 
                  restoreFocus(fe, type_cast<Window>(newFocusedWindow));
               
               break;
            }
         }
         
         RComponent realOppositeComponent = thisref->realOppositeComponent->get();
         if(realOppositeComponent != nullref && realOppositeComponent != fe->getOtherComponent())
         {
            fe = new FocusCausedEvent(newFocusOwner, FocusEvent::GOT_FOCUS,
                           fe->isTemporary(), realOppositeComponent, cause);
            
            type_cast<AWSEvent>(fe)->isPosted = true;
         }
         
         return typeAheadAssertions(newFocusOwner, fe);
      }
      
      case FocusEvent::LOST_FOCUS:
      {
         RFocusEvent fe = type_cast<FocusEvent>(e);
         RComponent currentFocusOwner = getFocusOwner();
         
         if(currentFocusOwner == nullref)
            break;
         
         // Ignore cases where a Component loses focus to itself.
         // If we make a mistake because of retargeting, then the
         // GOT_FOCUS handler will correct it.
         if(currentFocusOwner == fe->getOtherComponent())
            break;
         
         setFocusOwner(nullref);
         
         if(getFocusOwner() != nullref)
         {
            // Focus change was rejected. Unlikely, but possible.
            restoreFocus(currentFocusOwner, true);
            break;
         }
         
         if(!fe->isTemporary())
         {
            setPermanentFocusOwner(nullref);

            if(getPermanentFocusOwner() != nullref)
            {
               // Focus change was rejected. Unlikely, but possible.
               restoreFocus(currentFocusOwner, true);
               break;
            }
         }
         else
         {
            RWindow owningWindow = currentFocusOwner->getParentWindow();
            if(owningWindow != nullref)
               owningWindow->setTemporaryLostComponent(currentFocusOwner);
         }
         
         fe->setSource(currentFocusOwner);
         
         realOppositeComponent = (fe->getOtherComponent() != nullref)
            ? new Weak<Component>(currentFocusOwner)
            : NULL_COMPONENT_WR;
         
         return typeAheadAssertions(currentFocusOwner, fe);
      }
      
      case WindowEvent::WINDOW_DEACTIVATED:
      {
         RWindowEvent we = type_cast<WindowEvent>(e);
         RWindow currentActiveWindow = getActiveWindow();
         
         if(currentActiveWindow == nullref)
            break;
         
         if(currentActiveWindow != e->getSource())
         {
            // The event is lost in time.
            // Allow listeners to precess the event
            // but do not change any states
            break;
         }
         
         setActiveWindow(nullref);
         if(getActiveWindow() != nullref)
         {
            // Activation change was rejected. Unlikely, but possible.
            break;
         }
         
         we->setSource(currentActiveWindow);
         
         return typeAheadAssertions(currentActiveWindow, we);
      }
      
      case WindowEvent::WINDOW_LOST_FOCUS:
      {
         RWindowEvent we = type_cast<WindowEvent>(e);
         RWindow currentFocusedWindow = getFocusedWindow();
         RWindow oppositeWindow = we->getOtherWindow();
         RWindow losingFocusWindow = we->getWindow();
         RWindow activeWindow = getActiveWindow();
         
         if(currentFocusedWindow == nullref)
            break;
         
         // Special case -- if the windowing system posts an event
         // claiming that the active Window has lost focus to the
         // focused Window, then discard the event. This is an artifact
         // of the windowing system not knowing which Window is really focused.
         if(inSendMessage == 0 && losingFocusWindow == activeWindow &&
            oppositeWindow == currentFocusedWindow)
         {
            break;
         }
         
         RComponent currentFocusOwner = getFocusOwner();
         if(currentFocusOwner != nullref)
         {
            // The focus owner should always receive a
            // LOST_FOCUS event before the Window is defocused.
            RComponent oppositeComp = nullref;
            if(oppositeWindow != nullref)
            {
               oppositeComp = oppositeWindow->getTemporaryLostComponent();
               if(oppositeComp == nullref)
                  oppositeComp = oppositeWindow->getMostRecentFocusOwner();
            }
            
            if(oppositeComp == nullref)
               oppositeComp = oppositeWindow;
            
            sendMessage(currentFocusOwner,
                        new FocusCausedEvent(currentFocusOwner,
                                       FocusEvent::LOST_FOCUS,
                                       true,
                                       oppositeComp,
                                       FocusCausedEvent::Cause::ACTIVATION));
         }
         
         setFocusedWindow(nullref);
         if(getFocusedWindow() != nullref)
         {
            // Focus change was rejected. Unlikely, but possible.
            restoreFocus(currentFocusedWindow, nullref, true);
            break;
         }
         
         we->setSource(currentFocusedWindow);
         
         realOppositeWindow = (oppositeWindow == nullref)
            ? new Weak<Window>(currentFocusedWindow)
            : NULL_WINDOW_WR;

         typeAheadAssertions(currentFocusedWindow, we);
         
         if(oppositeWindow == nullref)
         {
            // Then we need to deactive the active Window as well.
            // No need to synthesize in other cases, because
            // WINDOW_ACTIVATED will handle it if necessary.
            sendMessage(activeWindow,
                        new WindowEvent(activeWindow,
                                    WindowEvent::WINDOW_DEACTIVATED,
                                    nullref));
            if (getActiveWindow() != nullref)
            {
               // Activation change was rejected. Unlikely,
               // but possible.
               
               restoreFocus(currentFocusedWindow, nullref, true);
            }
         }
         
         break;
      }
      
      case KeyEvent::KEY_TYPED:
      case KeyEvent::KEY_PRESSED:
      case KeyEvent::KEY_RELEASED:
         return typeAheadAssertions(nullref, e);
      
      default:
         return false;
   }

   return true;
}

vbool DefaultFocusManager::dispatchKeyEvent(RKeyEvent e)
{
   RComponent focusOwner = e->isPosted ? getFocusOwner() : e->getComponent();
   
   if(focusOwner != nullref && focusOwner->isShowing() &&
      focusOwner->isFocusable() && focusOwner->isEnabled())
   {
      if(!e->isConsumed())
      {
         RComponent comp = e->getComponent();
         
         if(comp != nullref && comp->isEnabled())
            redispatchEvent(comp, e);
      }
   }
   
   // in the event MenuBar and Menu systems become implemented
   // as a part of the AROLib then it'd be prudent to consider
   // adding the full functionality for KeyEvent Post Processing
   postProcessKeyEvent(e);

   return true;
}

vbool DefaultFocusManager::postProcessKeyEvent(RKeyEvent e)
{
   if(!e->isConsumed())
   {
      RComponent target = e->getComponent();

      RContainer p = type_of<Container>(target)
                        ? type_cast<Container>(target)
                        : target->getParent();

      if(p != nullref)
         p->postProcessKeyEvent(e);
   }

   return true;
}

void DefaultFocusManager::pumpApprovedKeyEvents()
{
   RKeyEvent ke;

   do
   {
      ke = nullref;
      
      sync_lock(thisref)
      {
         if(enqueuedKeyEvents->size() != 0)
         {
            ke = enqueuedKeyEvents->getFirst();

            if(typeAheadMarkers->size() != 0)
            {
               RTypeAheadMarker marker = typeAheadMarkers->getFirst();
               
               if(ke->getWhen() > marker->after)
                  ke = nullref;
            }
            
            if(ke != nullref)
               enqueuedKeyEvents->removeFirst();
         }
      }
      
      if(ke != nullref)
         preDispatchKeyEvent(ke);
   }
   while(ke != nullref);
}

vbool DefaultFocusManager::typeAheadAssertions(RComponent target, RAWSEvent e)
{
   // Clear any pending events here as well as in
   // the GOT_FOCUS handler. We need this call
   // here in case a marker was removed in
   // response to a call to dequeueKeyEvents.
   pumpApprovedKeyEvents();

   switch(e->getEventID())
   {
      case KeyEvent::KEY_TYPED:
      case KeyEvent::KEY_PRESSED:
      case KeyEvent::KEY_RELEASED:
      {
         RKeyEvent ke = type_cast<KeyEvent>(e);

         sync_lock(thisref)
         {
            if(e->isPosted && typeAheadMarkers->size() != 0)
            {
               RTypeAheadMarker marker = typeAheadMarkers->getLast();

               if(ke->getWhen() > marker->after)
               {
                  enqueuedKeyEvents->addLast(ke);

                  return true;
               }
            }
         }

         // KeyEvent was posted before focus change request
         return preDispatchKeyEvent(ke);
      }

      case FocusEvent::GOT_FOCUS:
      {
         // Search the marker list for the first marker tied to
         // the Component which just gained focus. Then remove
         // that marker, any markers which immediately follow
         // and are tied to the same component, and all markers
         // that preceed it. This handles the case where
         // multiple focus requests were made for the same
         // Component in a row and when we lost some of the
         // earlier requests. Since GOT_FOCUS events will
         // not be generated for these additional requests,
         // we need to clear those markers too.
         sync_lock(thisref)
         {
            vbool found = false;
            if(hasMarker(target))
            {
               for(RIterator<TypeAheadMarker> iter = typeAheadMarkers->iterator(); iter->hasNext();)
               {
                  if(iter->next()->untilFocused == target)
                     found = true;
                  else if(found)
                     break;

                  iter->remove();
               }
            }
         }

         redispatchEvent(target, e);

         // Now, dispatch any pending KeyEvents which have been
         // released because of the GOT_FOCUS event so that we
         // don't have to wait for another event to be posted
         // to the queue.
         pumpApprovedKeyEvents();
         return true;
      }

      default:
      {
         redispatchEvent(target, e);
         return true;
      }
   }
}

vbool DefaultFocusManager::hasMarker(RComponent comp)
{
   for(RIterator<TypeAheadMarker> iter = typeAheadMarkers->iterator(); iter->hasNext();)
   {
      if(iter->next()->untilFocused == comp)
         return true;
   }

   return false;
}

void DefaultFocusManager::clearMarkers()
{
   sync_lock(thisref)
   {
      typeAheadMarkers->clear();
   }
}

vbool DefaultFocusManager::preDispatchKeyEvent(RKeyEvent ke)
{
   if(ke->isPosted)
   {
      RComponent focusOwner = getFocusOwner();

      ke->setSource((focusOwner != nullref) ? focusOwner : type_cast<Component>(getFocusedWindow()));
   }

   if(ke->getSource() == nullref)
      return true;

   EventQueue::setCurrentEventAndMostRecentTime(ke);

   return dispatchKeyEvent(ke);
}

void DefaultFocusManager::focusNextComponent(RComponent current)
{
   if(current != nullref)
      current->transferFocus();
}

void DefaultFocusManager::focusPreviousComponent(RComponent current)
{
   if(current != nullref)
      current->transferFocusBackward();
}

void DefaultFocusManager::processKeyEvent(RComponent comp, RKeyEvent e)
{
   if(consumeProcessedKeyEvent(e))
      return;
   
   // KEY_TYPED events cannot be focus traversal keys
   if(e->getEventID() == KeyEvent::KEY_TYPED)
      return;
   
   if(!e->isConsumed())
   {
      RKeyStroke stroke = KeyStroke::getKeyStrokeForEvent(e),
               oppStroke = KeyStroke::getKeyStroke(stroke->getKeyCode(),
                                          stroke->getModifiers(),
                                          !stroke->isOnRelease());
      
      RList<KeyStroke> toTest;
      vbool contains, containsOpp;
      
      toTest = getFocusTraversalKeys(FocusManager::FOCUS_NEXT_KEYS);
      contains = toTest->contains(stroke);
      containsOpp = toTest->contains(oppStroke);
      
      if(contains || containsOpp)
      {
         consumeTraversalKey(e);
         
         if(contains)
            focusNextComponent(comp);
         
         return;
      }
	  else if(e->getEventID() == KeyEvent::KEY_PRESSED)
      {
         consumeNextTypedKey = false;
      }
      
      toTest = getFocusTraversalKeys(FocusManager::FOCUS_PREV_KEYS);
      contains = toTest->contains(stroke);
      containsOpp = toTest->contains(oppStroke);
      
      if(contains || containsOpp)
      {
         consumeTraversalKey(e);
         
         if(contains)
            focusPreviousComponent(comp);
      }
   }
}

void DefaultFocusManager::enqueueKeyEvents(vlong after, RComponent untilFocused)
{
   sync_lock(thisref)
   {
      if(untilFocused == nullref)
         return;
      
      vint insertionIndex = 0, i = typeAheadMarkers->size();
      RListIterator<TypeAheadMarker> iter = typeAheadMarkers->listIterator(i);
      
      for(; i>0; i--)
      {
         RTypeAheadMarker marker = iter->previous();
         
         if(marker->after <= after)
         {
            insertionIndex = i;
            break;
         }
      }
      
      typeAheadMarkers->add(insertionIndex, new TypeAheadMarker(after, untilFocused));
   }
}

void DefaultFocusManager::dequeueKeyEvents(vlong after, RComponent untilFocused)
{
   sync_lock(thisref)
   {
      if(untilFocused == nullref)
         return;
      
      RTypeAheadMarker marker;
      RListIterator<TypeAheadMarker> iter = typeAheadMarkers->listIterator(
                                    (after>=0) ? typeAheadMarkers->size() : 0);
      if(after < 0)
      {
         while(iter->hasNext())
         {
            marker = iter->next();
            if(marker->untilFocused == untilFocused)
            {
               iter->remove();
               return;
            }
         }
      }
      else
      {
         while(iter->hasPrevious())
         {
            marker = iter->previous();
            if(marker->untilFocused == untilFocused && marker->after == after)
            {
               iter->remove();
               return;
            }
         }
      }
   }
}

void DefaultFocusManager::discardKeyEvents(RComponent comp)
{
   sync_lock(thisref)
   {
      if(comp == nullref)
         return;
      
      vlong start = -1;

      for(RIterator<TypeAheadMarker> iter = typeAheadMarkers->iterator(); iter->hasNext(); )
      {
         RTypeAheadMarker marker = iter->next();
         RComponent toTest = marker->untilFocused;
         vbool match = (toTest == comp);

         while(!match && toTest != nullref && !type_of<Window>(toTest))
         {
            toTest = toTest->getParent();
            match = (toTest == comp);
         }

         if(match)
         {
            if(start < 0)
               start = marker->after;

            iter->remove();
         }
         else if(start >= 0)
         {
            purgeStampedEvents(start, marker->after);
            start = -1;
         }
      }

      purgeStampedEvents(start, -1);
   }
}

void DefaultFocusManager::purgeStampedEvents(vlong start, vlong end)
{
   if(start < 0)
      return;

   for(RIterator<KeyEvent> iter = enqueuedKeyEvents->iterator(); iter->hasNext(); )
   {
      RKeyEvent ke = iter->next();
      vlong time = ke->getWhen();

      if(start < time && (end < 0 || time <= end))
         iter->remove();

      if(end >= 0 && time > end)
         break;
   }
}

void DefaultFocusManager::consumeNextKeyTyped(RKeyEvent e)
{
   consumeNextTypedKey = true;
}

void DefaultFocusManager::consumeTraversalKey(RKeyEvent e)
{
   e->consume();
   consumeNextTypedKey = (e->getEventID() == KeyEvent::KEY_PRESSED) &&
                           !e->isActionKey();
}

vbool DefaultFocusManager::consumeProcessedKeyEvent(RKeyEvent e)
{
	if((e->getEventID() == KeyEvent::KEY_TYPED) && consumeNextTypedKey)
   {
      e->consume();
      consumeNextTypedKey = false;
      return true;
   }
   
   return false;
}

RWindow DefaultFocusManager::getOwningFrameDialog(RWindow window)
{
   while(window != nullref && !(type_of<Frame>(window) || type_of<Dialog>(window)))
      window = type_cast<Window>(window->getParent());
   
   return window;
}

vbool DefaultFocusManager::sendMessage(RComponent target, RAWSEvent e)
{
   RFocusManager mngr = getFocusManager();
   
   RDefaultFocusManager defMngr = type_of<DefaultFocusManager>(mngr) ?
      type_cast<DefaultFocusManager>(mngr) : nullref;
   
   if(defMngr != nullref)
   {
      sync_lock(defMngr)
	  {
         defMngr->inSendMessage++;
	  }
   }
   
   System::getEventQueue()->dispatchEvent(e);
   
   if(defMngr != nullref)
   {
      sync_lock(defMngr)
	  {
         defMngr->inSendMessage--;
	  }
   }
   
   return true;
}

 /*
  * This series of restoreFocus methods is used for recovering from a
  * rejected focus or activation change. Rejections typically occur when
  * the user attempts to focus a non-focusable Component or Window.
  */
void DefaultFocusManager::restoreFocus(RWindowEvent we)
{
	if(we->getOtherWindow() != nullref &&
		restoreFocus(we->getOtherWindow(), nullref, false))
   {
   }
   else
   {
      clearFocusOwner();
   }
}

void DefaultFocusManager::restoreFocus(RFocusEvent fe, RWindow newFocusedWindow)
{
   RComponent vetoedComponent = fe->getComponent();
   
   if(newFocusedWindow != nullref && restoreFocus(newFocusedWindow, 
                                                  vetoedComponent, false))
   {
   }
   else if(fe->getOtherComponent() != nullref &&
                doRestoreFocus(fe->getOtherComponent(), vetoedComponent, false))
   {
   }
   else
   {
      clearFocusOwner();
   }
}

vbool DefaultFocusManager::restoreFocus(RWindow aWindow, RComponent vetoedComponent, 
                              vbool clearOnFailure)
{
   RComponent toFocus = FocusManager::getMostRecentFocusOwner(aWindow);
   
   if(toFocus != nullref && toFocus != vetoedComponent && doRestoreFocus(toFocus, vetoedComponent, false))
   {
      return true;
   }
   else if(clearOnFailure)
   {
      clearFocusOwner();
      
      return true;
   }
   else
   {
      return false;
   }
}

vbool DefaultFocusManager::restoreFocus(RComponent toFocus, vbool clearOnFailure)
{
   return doRestoreFocus(toFocus, nullref, clearOnFailure);
}

vbool DefaultFocusManager::doRestoreFocus(RComponent toFocus, RComponent vetoedComponent,
			   vbool clearOnFailure)
{
   if(toFocus->isShowing() && toFocus->isFocusable() &&
         toFocus->requestFocus(false, FocusCausedEvent::Cause::ROLLBACK))
   {
      return true;
   }
   else
   {
      RWindow root = toFocus->getParentWindow();
      RComponent nextFocus = nullref;
      
      if(root != nullref)
      {
         RFocusPolicy policy = FocusManager::getFocusManager()->getFocusPolicy();
         
         nextFocus = policy->getNext(root, toFocus);
         
         if(toFocus == nullref)
            nextFocus = policy->getDefault(root);
      }
      
      if(nextFocus != vetoedComponent && nextFocus != nullref &&
          nextFocus->requestFocusHelper(false, false, FocusCausedEvent::Cause::FOCUS_NEXT))
      {
         return true;
      }
      else if(clearOnFailure)
      {
         clearFocusOwner();
         
         return true;
      }
      else
      {
         return false;
      }
   }
}

DefaultFocusManager::TypeAheadMarker::TypeAheadMarker(vlong after, RComponent comp)
{
   thisref->untilFocused = comp;
   thisref->after = after;
}

} /* namespace aws */

} /* namespace aro */
