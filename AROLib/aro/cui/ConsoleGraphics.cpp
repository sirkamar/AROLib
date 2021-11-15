#include <aro/core.hpp>
#include <aro/aws/Point.hpp>
#include <aro/cui/Console.hpp>
#include <aro/aws/Component.hpp>
#include <aro/aws/Dimension.hpp>
#include <aro/aws/Rectangle.hpp>
#include <aro/cui/ConsoleGraphics.hpp>
#include <aro/aws/event/PaintEvent.hpp>

namespace aro {

namespace cui {

ConsoleGraphics::ConsoleGraphics(aws::event::RPaintEvent e)
{
   initBounds(e->getComponent(), e->getUpdateRect());
   
   //aws::RComponent c = e->getComponent();
   //aws::RRectangle r = e->getUpdateRect();
   //aws::RDimension s = Console::getSize();
   //
   //if(r->height > s->height) r->height = s->height;
   //if(r->width > s->width) r->width = s->width;
   //if(r->y < 0) r->y=0; if(r->x < 0) r->x=0;
   //
   //setDrawingChars('+','|','-');
   //shown = c->isShowing();
   //bottom = r->y+r->height;
   //right = r->x+r->width;
   //left=r->x; top=r->y;
}

void ConsoleGraphics::clear()
{
   //RStringBuilder clr = new StringBuilder("");
   //RString space = " ";
   //for(vint n=left; n<right; n++)
   //   clr->append(space);
   //
   //RString out = clr->toString();
   //
   //for(vint n=top; n<bottom; n++)
   //{
   //   Console::moveCursor(left, n);
   //   Console::putString(out);
   //}
   
   clearRectangle(left, top, right-left+1, bottom-top+1);
}

vchar ConsoleGraphics::getEdgeChar()
{
   return corner;
}

vchar ConsoleGraphics::getVerticalChar()
{
   return vert;
}

vchar ConsoleGraphics::getHorizontalChar()
{
   return horz;
}

void ConsoleGraphics::setEdgeChar(vchar e)
{
   corner = e;
}

void ConsoleGraphics::setVerticalChar(vchar v)
{
   vert = v;
}

void ConsoleGraphics::setHorizontalChar(vchar h)
{
   horz = h;
}

void ConsoleGraphics::setDrawingChars(vchar e, vchar v, vchar h)
{
   setEdgeChar(e);
   setVerticalChar(v);
   setHorizontalChar(h);
}

void ConsoleGraphics::initBounds(aws::RComponent c)
{
   initBounds(c, c->getBounds());
}

void ConsoleGraphics::initBounds(aws::RComponent c, aws::RRectangle r)
{
   aws::RDimension s = Console::getSize();
   
   if(r->height > s->height) r->height = s->height;
   if(r->width > s->width) r->width = s->width;
   if(r->y < 0) r->y=0; if(r->x < 0) r->x=0;
   
   setDrawingChars('+','|','-');
   shown = c->isShowing();
   bottom = r->y+r->height-1;
   right = r->x+r->width-1;
   left=r->x; top=r->y;
}

void ConsoleGraphics::drawString(vint X, vint Y, RString str)
{
   if(!shown) // if not isShowing()
      return;
   
   if((X|Y) < 0) // if negative
      return;
   
   if(X>=right-left+1 || Y>=bottom-top+1) // if invalid
      return;
   
   // get at most component width chars from string
   if(str->length() > right-(left+X))
      str = str->substring(0, right-(left+X));
   
   Console::moveCursor(left+X, top+Y);
   
   Console::putString(str);
}

void ConsoleGraphics::drawVerticalLine(vint X, vint Y, vint len)
{
   if(!shown) // if not isShowing()
      return;
   
   if((X|Y|len) < 0) // if negative
      return;
   
   if(left+X>right || top+Y>bottom) // if invalid starting point
      return;
   
   for(vint n=0; n<len && top+Y+n<=bottom; n++)
   {
      Console::moveCursor(left+X,top+Y+n);
      Console::putChar(vert);
   }
}

void ConsoleGraphics::drawHorizontalLine(vint X, vint Y, vint len)
{
   if(!shown) // if not isShowing()
      return;
   
   if((X|Y|len) < 0) // if negative
      return;
   
   if(left+X>right || top+Y>bottom) // if invalid starting point
      return;
   
   for(vint n=0; n<len && left+X+n<=right; n++)
   {
      Console::moveCursor(left+X+n,top+Y);
      Console::putChar(horz);
   }
}

void ConsoleGraphics::drawRectangle(vint X, vint Y, vint W, vint H)
{
   if(!shown) // if not isShowing()
      return;
   
   if((X|Y|W|H) < 0) // if negative
      return;
   
   if(left+X>right || top+Y>bottom)
      return;
   
   // draw left
   drawVerticalLine(X, Y + 1, H - 2);

   // draw top
   drawHorizontalLine(X + 1, Y, W - 2);

   // draw right
   drawVerticalLine(X + W - 1, Y + 1, H - 2);

   // draw bottom
   drawHorizontalLine(X + 1, Y + H - 1, W - 2);

   // draw the corners
   Console::moveCursor(left + X, top + Y); Console::putChar(corner);
   
   if(left + X + W - 1 <= right) { // if valid
      Console::moveCursor(left + X + W - 1, top + Y); Console::putChar(corner);
   }
   
   if(top + Y + H - 1 <= bottom) {// if valid
      Console::moveCursor(left + X, top + Y + H - 1); Console::putChar(corner);
   }
   
   if(left + X + W - 1 <= right && top + Y + H - 1 <= bottom) {// if valid
      Console::moveCursor(left + X + W - 1, top + Y + H - 1); Console::putChar(corner);
   }
}

void ConsoleGraphics::clearRectangle(vint X, vint Y, vint W, vint H)
{
   RStringBuilder clr = new StringBuilder("");
   RString space = " ";
   for(vint n=X; n<X+W; n++)
      clr->append(space);
   
   RString out = clr->toString();

   for(vint n=Y; n<Y+H; n++)
   {
      Console::moveCursor(X, n);
      Console::putString(out);
   }
}

} /* namespace cui */

} /* namespace aro */
