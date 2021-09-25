#include <aro/core.h>
#include <aro/aws/Insets.h>
#include <aro/aws/Graphics.h>
#include <aro/cui/CSRadioButton.h>
#include <aro/cui/border/LineBorder.h>

namespace aro {

namespace cui {

using namespace aws;

CSRadioButton::CSRadioButton()
   :CSRadioButton("")
{
   //setBorder(new LineBorder());
}

CSRadioButton::CSRadioButton(RString str)
{
   text = str;
   border = new LineBorder();
}

void CSRadioButton::paintComponent(RGraphics g)
{
   CSAbstractButton::paintComponent(g);
   
   if(isShowing())
   {
      int x, y;
      RInsets in = getInsets();
      int chgt = getSize()->height - (in->top+in->bottom);
      
      x = in->left; // horizontal LEFT
      
      y = in->top + chgt/2;  // vertical CENTER
      
      g->drawRectangle(x,y,3,3);

      if(isSelected())
         g->drawString(x+1,y+1,"*");
      
      g->drawString(x+4, y+1, text);
   }
}

RDimension CSRadioButton::getMinimumSize()
{
   return new Dimension(6,3);
}

RDimension CSRadioButton::getPreferredSize()
{
   return new Dimension(text->length()+6,3);
}

} /* namespace cui */

} /* namespace aro */
