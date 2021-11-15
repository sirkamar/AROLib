#include <aro/aws/Insets.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/Component.hpp>
#include <aro/cui/ConsoleGraphics.hpp>
#include <aro/cui/border/StarBorder.hpp>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

RInsets StarBorder::getInsets(RInsets insets)
{
   insets->set(1, 1, 1, 1);
   return insets;
}

void StarBorder::paintBorder(RComponent c, RGraphics g,
                             vint x, vint y, vint width, vint height)
{
   if(type_of<ConsoleGraphics>(g))
   {
      RConsoleGraphics cg = type_cast<ConsoleGraphics>(g);

      vchar e = cg->getEdgeChar();
      vchar v = cg->getVerticalChar();
      vchar h = cg->getHorizontalChar();
      
      if(c->isFocused())
         cg->setDrawingChars(e, e, e);
      else
         cg->setDrawingChars('*', '*', '*');
      
      g->drawRectangle(x, y, width, height);
      
      cg->setDrawingChars(e, v, h);
   }
   else
   {
      //manually draw rectangle outline one 'star' at a time
      for(vint row = y; row < y + height; row++)
      {
         for(vint col = x; col < x + width; col++)
         {
            // draw a 'star' in the first and last rows and columns
            if(row == y || row == y + height - 1 || col == x || col == x + width - 1)
            {
               g->drawString(row, col, "*");
            }
         }
      }
   }
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
