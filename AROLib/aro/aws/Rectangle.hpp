#ifndef AWS_RECTANGLE_H
#define AWS_RECTANGLE_H

#include <aro/core/String.hpp>

namespace aro {

namespace aws {

class Point;
class Rectangle;
typedef Ref<Point> RPoint;
typedef Ref<class Rectangle> RRectangle;

class Rectangle extends public Object implements public io::Streamable<Rectangle>
{
   public:
      vint x, y;
      vint width, height;
      
      Rectangle();
      Rectangle(RRectangle rect);
      Rectangle(vint width,vint height);
      Rectangle(vint x,vint y,vint width,vint height);
      
      virtual vbool contains(vint x,vint y,vint width,vint height);
      virtual void writeObject(io::RObjectOutputStream os);
      virtual void readObject(io::RObjectInputStream is);
      virtual vbool contains(RRectangle rect);
      virtual vbool equals(RObject obj);
      virtual RString toString();
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_RECTANGLE_H */
