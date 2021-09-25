#include <aro/core.h>
#include <aro/aws/Insets.h>
#include <aro/cui/CSTextBox.h>
#include <aro/aws/Graphics.h>
#include <aro/cui/border/LineBorder.h>
#include <aro/aws/event/KeyEvent.h>
#include <aro/aws/event/ActionEvent.h>
#include <aro/aws/event/ActionListener.h>

namespace aro {

namespace cui {

using namespace aws;
using namespace aws::event;

CSTextBox::CSTextBox()
   :CSTextBox(10)
{
   //echoChar = 0;
   //columns = 10;
   //isMod = false;
   //hTextPos = LEFT;
   //vTextPos = CENTER;
   //setBorder(new LineBorder());
}

CSTextBox::CSTextBox(int cols)
   :CSTextBox("", cols)
{
   //if(cols < 0)
   //   ex_throw new ArgumentException("columns less than zero");
   //
   //echoChar = 0;
   //isMod = false;
   //columns = cols;
   //hTextPos = LEFT;
   //vTextPos = CENTER;
   //setBorder(new LineBorder());
}

CSTextBox::CSTextBox(RString str)
   :CSTextBox(str, 10)
{
   //echoChar = 0;
   //isMod = false;
   //hTextPos = LEFT;
   //vTextPos = CENTER;
   //columns = str->length();
   //setBorder(new LineBorder());
}

CSTextBox::CSTextBox(RString str, int cols)
   :CSTextComponent(str)
{
   if(cols < 0)
      ex_throw new ArgumentException("CSTextBox columns less than zero");
   
   echoChar = 0;
   isMod = false;
   columns = cols;
   hTextPos = LEFT;
   vTextPos = CENTER;
   border = new LineBorder();
}

int CSTextBox::getColumns()
{
   return columns;
}

char CSTextBox::getEchoChar()
{
   return echoChar;
}

bool CSTextBox::isEchoCharSet()
{
   return echoChar != 0;
}

void CSTextBox::setEchoChar(char c)
{
   if(echoChar == c)
      return;
   
   RChar old = Char::valueOf(echoChar); echoChar = c;
   
   firePropertyChanged("echoChar", old, Char::valueOf(c));
}

void CSTextBox::setColumns(int cols)
{
   if(cols < 0)
      ex_throw new ArgumentException("columns less than zero");
   
   if(columns != cols)
   {
      columns = cols;
      invalidate();
   }
}

//void CSTextBox::handleInput(int key)
//{
//   if(!isEnabled())
//      return;
//   
//   if(isMod) // ignore if prev was modifier
//   {
//      isMod = false;
//      return;
//   }
//   
//   switch(key)
//   {
//      case 0: //MODIFIER
//         isMod = true;
//         break;
//      
//      case 8: //BACKSPACE
//         if(isEditable() && text->length() > 0)
//         {
//            text = text->substring(0, text->length()-1);
//            repaint();
//         }
//         break;
//      
//      case 13: //RETURN
//      {
//         RArray<Object> arr = listeners->getListeners();
//         
//         RActionEvent e = new ActionEvent(thisref,
//                              ActionEvent::ACTION_OCCURRED, text);
//         
//         for(int n=0; n<arr->length; n++)
//         {
//            if(arr[n]->isTypeOf<ActionListener>())
//            {
//               RActionListener ral = static_cast<ActionListener>(arr[n]);
//               
//               ral->actionOccurred(e);
//            }
//         }
//         
//         break;
//      }
//      
//      default:
//         if(isEditable() && key >= 32) //SPACE or higher
//         {
//            text += String::valueOf((char)key);
//            repaint();
//         }
//         break;
//   }
//}

RDimension CSTextBox::getMinimumSize()
{
   //RDimension d = CSTextComponent::getMinimumSize();
   //
   //if(d != nullref)
   //   return d;
   
   RInsets ins = getInsets();
   
   return new Dimension(2+ins->left+ins->right, 1+ins->top+ins->bottom);
}

RDimension CSTextBox::getPreferredSize()
{
   //RDimension d = CSTextComponent::getPreferredSize();
   //
   //if(d != nullref)
   //   return d;
   
   RInsets ins = getInsets();
   
   int w = Math::maximum(columns, 2), h = 1;
   
   return new Dimension(w+ins->left+ins->right, h+ins->top+ins->bottom);
}

int CSTextBox::getVerticalTextPosition()
{
   return vTextPos;
}

int CSTextBox::getHorizontalTextPosition()
{
   return hTextPos;
}

void CSTextBox::setVerticalTextPosition(int vpos)
{
   if(vpos != TOP && vpos != BOTTOM && vpos != CENTER)
      ex_throw new ArgumentException("Use CUIConstants positions TOP, "
                                  "BOTTOM or CENTER only.");
   
   if(vTextPos == vpos)
      return;
   
   RInt old = Int::valueOf(vTextPos); vTextPos = vpos;
   
   firePropertyChanged("verticalTextPosition", old, Int::valueOf(vpos));
}

void CSTextBox::setHorizontalTextPosition(int hpos)
{
   if(hpos != LEFT && hpos != RIGHT && hpos != CENTER)
      ex_throw new ArgumentException("Use CUIConstants positions LEFT, "
                                  "RIGHT or CENTER only.");
   
   if(hTextPos == hpos)
      return;
   
   RInt old = Int::valueOf(hTextPos); hTextPos = hpos;
   
   firePropertyChanged("horizontalTextPosition", old, Int::valueOf(hpos));
}

void CSTextBox::addActionListener(RActionListener l)
{
   listeners->add<ActionListener>(l);
}

void CSTextBox::removeActionListener(RActionListener l)
{
   listeners->add<ActionListener>(l);
}

void CSTextBox::paintComponent(RGraphics g)
{
   CSTextComponent::paintComponent(g);
   
   if(!isShowing())
      return;
   
   int x, y;
   RInsets in = getInsets();
   int twid = text->length();
   int cwid = getSize()->width - (in->left+in->right);
   int chgt = getSize()->height - (in->top+in->bottom);
   
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
   
   if(echoChar == 0)
      g->drawString(x, y, text->toString());
   else
      g->drawString(x, y, getEchoText());
}

RString CSTextBox::getEchoText()
{
   // if invalid echo char do not mask text
   if(echoChar < ' ' && echoChar > '~')
      return text->toString();
   
   RArray<vchar> arr = new Array<vchar>(text->length());
   
   for(int n=0; n<arr->length; n++)
      arr[n] = echoChar;
   
   return new String(arr);
}

void CSTextBox::fireActionOccurred()
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   RActionEvent e = new ActionEvent(thisref,
      ActionEvent::ACTION_OCCURRED, text->toString());
   
   for (int n = 0; n<arr->length; n++)
   {
      if(type_of<ActionListener>(arr[n]))
      {
         RActionListener ral = type_cast<ActionListener>(arr[n]);
         
         ral->actionOccurred(e);
      }
   }
}

void CSTextBox::processComponentKeyEvent(RKeyEvent e)
{
   int eventID = e->getEventID();
   
   if(eventID == KeyEvent::KEY_TYPED)
   {
      vchar c = e->getKeyChar();

      // no check done here for component enabled;
      // that should've been done by FocusManager
      if (isEditable() && c != KeyEvent::VKEY_ENTER)
      {
         if (c == KeyEvent::VKEY_BACKSPACE)
            text->setLength(text->length()-1);
         else
         {
            vint mod = e->getModifiers();
            
            text->append(String::valueOf(c));
         }

         // prevent passing on
         // to key listeners
         e->consume();
         
         repaint();
      }
   }
   else if(eventID == KeyEvent::KEY_RELEASED)
   {
      // no check done here for component enabled;
      // that should've been done by FocusManager
      if(e->getKeyCode() == KeyEvent::VKEY_ENTER)
      {
         fireActionOccurred();
         
         //should consume KeyEvent?
         e->consume();
      }
   }
}

} /* namespace cui */

} /* namespace aro */
