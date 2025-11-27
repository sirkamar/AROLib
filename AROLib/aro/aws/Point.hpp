#ifndef AWS_POINT_H
#define AWS_POINT_H

#include <aro/core.hpp>

namespace aro {

namespace aws {

class Point;
typedef Ref<Point> RPoint;

class Point extends public Object, public io::Streamable<Point>
{
   public:
      vint x, y;
      
      Point();
      Point(RPoint pos);
      Point(vint x, vint y);
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
      
      void move(vint dx, vint dy);
      void set(vint x, vint y);
      vint getX();
      vint getY();
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_POINT_H */
