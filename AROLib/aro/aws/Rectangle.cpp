#include <aro/core.hpp>
#include <aro/aws/Rectangle.hpp>

namespace aro {

namespace aws {

Rectangle::Rectangle()
{
   x = y = width = height = 0;
}

Rectangle::Rectangle(RRectangle rect)
{
   height = rect->height;
   width = rect->width;
   x = rect->x;
   y = rect->y;
}

Rectangle::Rectangle(vint wide, vint high)
{
   height = high;
   width = wide;
   x = y = 0;
}

Rectangle::Rectangle(vint X, vint Y, vint wide, vint high)
{
   height = high;
   width = wide;
   x = X; y = Y;
}

RString Rectangle::toString()
{
   return getType() + " [x=" + String::valueOf(x) + ", y=" +
          String::valueOf(y) + ", width=" + String::valueOf(width) +
          ", height=" + String::valueOf(height) + "]";
}

vbool Rectangle::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Rectangle>(obj))
   {
      RRectangle r = type_cast<Rectangle>(obj);
      
      return r->x==x && r->y==y &&
             r->width==width && r->height==height;
   }
   
   return false;
}

vbool Rectangle::contains(RRectangle r)
{
   return contains(r->x, r->y, r->width, r->height);
}

void Rectangle::readObject(io::RObjectInputStream is)
{
   height = is->readInt();
   width = is->readInt();
   x = is->readInt();
   y = is->readInt();
}

void Rectangle::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(height);
   os->writeInt(width);
   os->writeInt(x);
   os->writeInt(y);
}

vbool Rectangle::contains(vint X, vint Y, vint W, vint H)
{
   vint w = thisref->width;
   vint h = thisref->height;
   
   if((w | h | W |H ) < 0)
      return false;
   
   int x = thisref->x;
   int y = thisref->y;
   if(X < x || Y < y)
      return false;
   
   w += x;
   W += X;
   if(W <= X)
   {
      if(w >= x || W > w)
         return false;
   }
   else
   {
      if(w >= x && W > w)
         return false;
   }
   
   h += y;
   H += Y;
   if(H <= Y)
   {
      if(h >= y || H > h)
         return false;
   }
   else
   {
      if(h >= y && H > h)
         return false;
   }

   return true;
}

} /* namespace aws */

} /* namespace aro */
