#include <aro/core.h>
#include <aro/aws/Insets.h>
#include <aro/aws/Rectangle.h>
#include <aro/aws/Component.h>
#include <aro/cui/ConsoleGraphics.h>
#include <aro/cui/border/AbstractBorder.h>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

AbstractBorder::AbstractBorder()
{
   
}

RInsets AbstractBorder::getInsets()
{
   return getInsets(new Insets());
}

//RInsets AbstractBorder::getInsets(RInsets insets)
//{
//   insets->left = insets->top = insets->right = insets->bottom = 0;
//   return insets;
//}

void AbstractBorder::paintBorder(RComponent c, RGraphics g)
{
   RRectangle r = c->getBounds();

   if(c->isFocusOwner() && type_of<ConsoleGraphics>(g))
   {
      RConsoleGraphics cg = type_cast<ConsoleGraphics>(g);

      vchar e = cg->getEdgeChar();
      vchar v = cg->getVerticalChar();
      vchar h = cg->getHorizontalChar();

      cg->setDrawingChars(e, e, e);

      paintBorder(c, cg, 0, 0, r->width, r->height);

      cg->setDrawingChars(e, v, h);
   }
   else
      paintBorder(c, g, 0, 0, r->width, r->height);
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
