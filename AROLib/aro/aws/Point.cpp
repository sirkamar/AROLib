#include <aro/core.hpp>
#include <aro/aws/Point.hpp>

namespace aro {

namespace aws {

Point::Point()
{
   set(0, 0);
}

Point::Point(RPoint p)
{
   set(p->x, p->y);
}

Point::Point(vint x, vint y)
{
   set(x, y);
}


RString Point::toString()
{
   return "[x=" + String::valueOf(x) +
          ",y=" + String::valueOf(y) + "]";
}

vbool Point::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Point>(obj))
   {
      RPoint p = type_cast<Point>(obj);
      
      return (p->x == x && p->y == y);
   }
   
   return false;
}

void Point::readObject(io::RObjectInputStream is)
{
   x = is->readInt();
   y = is->readInt();
}

void Point::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(x);
   os->writeInt(y);
}

void Point::move(vint dx, vint dy)
{
   x += dx;
   y += dy;
}

void Point::set(vint px, vint py)
{
   x = px;
   y = py;
}

vint Point::getX()
{
   return x;
}

vint Point::getY()
{
   return y;
}

} /* namespace aws */

} /* namespace aro */
