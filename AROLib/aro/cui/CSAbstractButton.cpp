#include <aro/aws/Insets.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/aws/event/ItemEvent.hpp>
#include <aro/aws/event/ActionEvent.hpp>
#include <aro/cui/CSAbstractButton.hpp>

namespace aro {

namespace cui {

using namespace aws::event;

const vint CSAbstractButton::ENABLED = 1 << 3;
const vint CSAbstractButton::PRESSED = 1 << 2;
const vint CSAbstractButton::SELECTED = 1 << 1;

CSAbstractButton::CSAbstractButton()
{
   stateMask = 0;
   setEnabled(true);
   setFocusable(true);
   mnemonicIndex = -1;
   hTextPos = vTextPos = CENTER;
}

vbool CSAbstractButton::isEnabled()
{
   return (stateMask & ENABLED) != 0;
}

vbool CSAbstractButton::isPressed()
{
   return (stateMask & PRESSED) != 0;
}

vbool CSAbstractButton::isSelected()
{
   return (stateMask & SELECTED) != 0;
}

void CSAbstractButton::setEnabled(vbool b)
{
   if(isEnabled() == b)
      return;

   Component::setEnabled(b);

   if(b)
      stateMask |= ENABLED;
   else
   {
      stateMask &= ~ENABLED;
      // unpress just in case
      stateMask &= ~PRESSED;
   }

   fireStateChanged();
}

void CSAbstractButton::setPressed(vbool b)
{
   if(isPressed() == b || !isEnabled())
      return;
   
   if(b)
      stateMask |= PRESSED;
   else
      stateMask &= ~PRESSED;
   
   if(!isPressed())
      fireActionOccurred(new ActionEvent(thisref, ActionEvent::ACTION_OCCURRED, getActionCommand()));

   fireStateChanged();
}

void CSAbstractButton::setSelected(vbool b)
{
   if(isEnabled() == b)
      return;

   if(b)
      stateMask |= SELECTED;
   else
      stateMask &= ~SELECTED;

   fireItemStateChanged(new ItemEvent(thisref, ItemEvent::ITEM_STATE_CHANGED,
                        thisref, b ? ItemEvent::SELECTED : ItemEvent::DESELECTED));

   fireStateChanged();
}

vint CSAbstractButton::getMnemonic()
{
   return mnemonic;
}

void CSAbstractButton::setMnemonic(vint key)
{
   vint oldValue = mnemonic;
   
   mnemonic = key;
   
   fireStateChanged();
   
   firePropertyChanged("mnemonic", new Int(oldValue), new Int(key));
   
   updateDisplayedMnemonicIndex(getText(), mnemonic);
   
   if(oldValue != key)
   {
      revalidate();
      repaint();
   }
}

RString CSAbstractButton::getText()
{
   return text;
}

void CSAbstractButton::setText(RString txt)
{
   RString oldText = text;

   text = txt;

   firePropertyChanged("text", oldText, text);

   updateDisplayedMnemonicIndex(text, getMnemonic());

   if(text == nullref || oldText == nullref || !text->equals(oldText))
   {
      revalidate();
      repaint();
   }
}

RString CSAbstractButton::getActionCommand()
{
   if(actionCommand == nullref)
      return getText();

   return actionCommand;
}

void CSAbstractButton::setActionCommand(RString str)
{
   actionCommand = str;
}

void CSAbstractButton::doClick()
{
   doClick(68);
}

void CSAbstractButton::doClick(vint pressTime)
{
   setPressed(true);
   repaint();
   Thread::sleep(pressTime);
   setPressed(false);
}

vint CSAbstractButton::getDisplayedMnemonicIndex()
{
   return mnemonicIndex;
}

void CSAbstractButton::setDisplayedMnemonicIndex(vint index)
{
   vint oldValue = mnemonicIndex;

   if(index == -1)
      mnemonicIndex = -1;
   else
   {
      RString text = getText();
      vint textLength = (text == nullref) ? 0 : text->length();

      if(index < -1 || index >= textLength)
         ex_throw new ArgumentException("index == " + String::valueOf(index));
   }

   mnemonicIndex = index;
   firePropertyChanged("displayedMnemonicIndex", new Int(oldValue), new Int(index));

   if(index != oldValue)
   {
      revalidate();
      repaint();
   }
}

RCSButtonGroup CSAbstractButton::getGroup()
{
   return group;
}

void CSAbstractButton::setGroup(RCSButtonGroup grp)
{
   group = grp;
}

aws::RDimension CSAbstractButton::getMinimumSize()
{
   //aws::RDimension d = CSComponent::getMinimumSize();
   //
   //if(d != nullref)
   //   return d;
   
   aws::RInsets ins = getInsets();
   
   return new aws::Dimension(2 + ins->left + ins->right, 1 + ins->top + ins->bottom);
}

aws::RDimension CSAbstractButton::getPreferredSize()
{
   //aws::RDimension d = CSComponent::getPreferredSize();
   //
   //if(d != nullref)
   //   return d;
   
   aws::RInsets ins = getInsets();
   
   vint h = mnemonicIndex < 0 ? 1 : 2;
   vint w = Math::maximum(text->length(), 2);
   
   return new aws::Dimension(w + ins->left + ins->right, h + ins->top + ins->bottom);
}

vint CSAbstractButton::getVerticalTextPosition()
{
   return vTextPos;
}

vint CSAbstractButton::getHorizontalTextPosition()
{
   return hTextPos;
}

void CSAbstractButton::setVerticalTextPosition(vint vpos)
{
   if(vpos != TOP && vpos != BOTTOM && vpos != CENTER)
      ex_throw new ArgumentException("Use CUIConstants text positions "
                                  "TOP, BOTTOM or CENTER only.");
   
   vint old = vTextPos;
   vTextPos = vpos;
   firePropertyChanged("verticalTextPosition", new Int(old), new Int(hTextPos));
   revalidate();
   repaint();
}

void CSAbstractButton::setHorizontalTextPosition(vint hpos)
{
   if(hpos != LEFT && hpos != RIGHT && hpos != CENTER)
      ex_throw new ArgumentException("Use CUIConstants text positions "
                                  "LEFT, RIGHT or CENTER only.");
   
   vint old = hTextPos;
   hTextPos = hpos;
   firePropertyChanged("horizontalTextPosition", new Int(old), new Int(hTextPos));
   revalidate();
   repaint();
}

RArray<Object> CSAbstractButton::getSelectedObjects()
{
   if(!isSelected())
      return nullref;

   RArray<Object> arr = new Array<Object>(1);
   arr[0] = getText();
   return arr;
}

void CSAbstractButton::addItemListener(RItemListener l)
{
   listeners->add<ItemListener>(l);
}

void CSAbstractButton::removeItemListener(RItemListener l)
{
   listeners->remove<ItemListener>(l);
}

RArray<ItemListener> CSAbstractButton::getItemListeners()
{
   return listeners->getListeners<ItemListener>();
}

void CSAbstractButton::fireItemStateChanged(RItemEvent e)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   for(vint i = 0; i < arr->length; i++)
   {
      if(type_of<ItemListener>(arr[i]))
      {
         RItemListener ril = type_cast<ItemListener>(arr[i]);
         
         ril->itemStateChanged(e);
      }
   }
}

void CSAbstractButton::addChangeListener(event::RChangeListener l)
{
   listeners->add<event::ChangeListener>(l);
}

void CSAbstractButton::removeChangeListener(event::RChangeListener l)
{
   listeners->remove<event::ChangeListener>(l);
}

RArray<event::ChangeListener> CSAbstractButton::getChangeListeners()
{
   return listeners->getListeners<event::ChangeListener>();
}

void CSAbstractButton::fireStateChanged()
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   for(vint i = 0; i < arr->length; i++)
   {
      if(type_of<event::ChangeListener>(arr[i]))
      {
         event::RChangeListener rcl = type_cast<event::ChangeListener>(arr[i]);
         
         if(changeEvent == nullref)
            changeEvent = new event::ChangeEvent(thisref);

         rcl->stateChanged(changeEvent);
      }
   }
}

void CSAbstractButton::addActionListener(RActionListener l)
{
   listeners->add<ActionListener>(l);
}

void CSAbstractButton::removeActionListener(RActionListener l)
{
   listeners->remove<ActionListener>(l);
}

RArray<ActionListener> CSAbstractButton::getActionListeners()
{
   return listeners->getListeners<ActionListener>();
}

void CSAbstractButton::fireActionOccurred(RActionEvent e)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   for(vint i = 0; i < arr->length; i++)
   {
      if(type_of<ActionListener>(arr[i]))
      {
         RActionListener ral = type_cast<ActionListener>(arr[i]);
         
         ral->actionOccurred(e);
      }
   }
}

void CSAbstractButton::updateDisplayedMnemonicIndex(RString text, vint mnemonic)
{
   // search for mnemonic character index in string
   setDisplayedMnemonicIndex(text->indexOf(mnemonic));
}

void CSAbstractButton::processKeyEvent(RKeyEvent e)
{
   // this gives the key event listeners a crack at the event
   Component::processKeyEvent(e);
   
   // give the component itself a crack at the event
   if(!e->isConsumed())
   {
      // process event locally
      // check for spacebar or return key

      if(e->getEventID() == KeyEvent::KEY_TYPED)
      {
         vint keyCode = e->getKeyChar();

         if(keyCode == KeyEvent::VKEY_SPACE || keyCode == KeyEvent::VKEY_ENTER)
            setPressed(true);

         e->consume();
      }

      else if(e->getEventID() == KeyEvent::KEY_RELEASED)
      {
         vint keyCode = e->getKeyCode();

         if(keyCode == KeyEvent::VKEY_SPACE || keyCode == KeyEvent::VKEY_ENTER)
            setPressed(false);

         e->consume();
      }
   }
}

/*void CSAbstractButton::paintComponent(RGraphics g)
{
   CSComponent::paintComponent(g);
   
   vint x, y;
   RInsets in = getInsets();
   vint twid = text->length();
   vint cwid = getSize()->width - (in->left+in->right);
   vint chgt = getSize()->height - (in->top+in->bottom);
   
   if(twid > cwid || hTextPos == LEFT)
      x = in->left;
   else if(hTextPos == CENTER)
      x = in->left + cwid/2 - twid/2;
   else
      x = in->left + cwid - twid;
   
   if(vTextPos == TOP)
      y = in->top;
   else if(vTextPos == CENTER)
      y = in->top + chgt/2;
   else
      y = in->top + chgt - 1;
   
   g->drawString(x, y, text);
}*/

} /* namespace cui */

} /* namespace aro */
