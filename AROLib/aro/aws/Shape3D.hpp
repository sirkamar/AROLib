#ifndef AWS_SHAPE3D_H
#define AWS_SHAPE3D_H

#include <aro/aws/Shape.hpp>

namespace aro {

namespace aws {

interface Shape3D;
typedef Ref<Shape3D> RShape3D;

interface Shape3D extends Shape
{
	virtual vdouble calculateVolume() = 0;
	virtual vdouble calculateSurfaceArea() = 0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_SHAPE3D_H */
