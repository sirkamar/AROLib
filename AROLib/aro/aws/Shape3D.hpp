#ifndef AWS_SHAPE3D_H
#define AWS_SHAPE3D_H

#include <aro/aws/Shape.h>

namespace aro {

namespace aws {

interface Shape3D;
typedef Ref<Shape3D> RShape3D;

interface Shape3D : Shape
{
	virtual vdouble getSurfaceArea() = 0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_SHAPE3D_H */
