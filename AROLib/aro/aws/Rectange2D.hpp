#ifndef AWS_RECTANGLE2D_H
#define AWS_RECTANGLE2D_H

#include <aro/aws/Shape2D.hpp>

namespace aro {

namespace aws {

class Rectangle2D;
typedef Ref<Rectangle2D> RRectangle2D;

class Rectangle2D : public Object, public Shape2D, public io::Streamable<Rectangle2D>
{
	public:
	  Rectangle2D();
	  Rectangle2D(RRectangle2D rect);
	  Rectangle2D(vdouble length, vdouble width);
      
	  virtual void setLength(vdouble length);
	  virtual void setWidth(vdouble width);
	  virtual vdouble getLength();
	  virtual vdouble getWidth();
      
	  virtual vdouble calculateArea();
	  virtual vdouble calculatePerimeter();

	  virtual vint hashCode();
	  virtual RString toString();
	  virtual vbool equals(RObject obj);
	  virtual void readObject(io::RObjectInputStream is);
	  virtual void writeObject(io::RObjectOutputStream os);

	private:
		vdouble length;
		vdouble width;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_RECTANGLE2D_H */
