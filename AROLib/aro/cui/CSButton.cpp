#include <aro/aws/Insets.hpp>
#include <aro/cui/CSButton.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/aws/event/ActionEvent.hpp>
#include <aro/cui/border/LineBorder.hpp>

namespace aro {

using aws::event::KeyEvent;
using aws::event::ActionEvent;

namespace cui {

CSButton::CSButton()
   :CSButton("")
{
   //setBorder(new border::LineBorder());
}

CSButton::CSButton(RString str)
{
   text = str;
   border = new border::LineBorder();
}

void CSButton::processComponentKeyEvent(aws::event::RKeyEvent e)
{
   int eventID = e->getEventID();
   
   if(eventID == KeyEvent::KEY_RELEASED)
   {
      vint keyCode = e->getKeyCode();
      
      if(keyCode == KeyEvent::VKEY_ENTER || keyCode == KeyEvent::VKEY_SPACE)
      {
         fireActionOccurred(new ActionEvent(thisref, ActionEvent::ACTION_OCCURRED, text));
         
         //should consume KeyEvent?
         e->consume();
      }
   }
}

void CSButton::paintComponent(aws::RGraphics g)
{
   CSAbstractButton::paintComponent(g);
   
   int x, y;
   int hTextPos = getHorizontalTextPosition();
   int vTextPos = getVerticalTextPosition();

   aws::RInsets in = getInsets();
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
   
   g->drawString(x, y, text);
}

} /* namespace cui */

} /* namespace aro */
