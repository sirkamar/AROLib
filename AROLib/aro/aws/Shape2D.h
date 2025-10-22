#ifndef AWS_SHAPE2D_H
#define AWS_SHAPE2D_H

#include <aro/aws/Shape.h>

namespace aro {

namespace aws {

interface Shape2D;
typedef Ref<Shape2D> RShape2D;

interface Shape2D : Shape
{
	virtual vdouble getPerimeter() = 0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_SHAPE2D_H */
