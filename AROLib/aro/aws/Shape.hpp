#ifndef AWS_SHAPE_H
#define AWS_SHAPE_H

#include <aro/core/Interface.hpp>

namespace aro {

namespace aws {

interface Shape;
typedef Ref<Shape> RShape;

interface Shape : Interface
{
	virtual vdouble calculateArea() = 0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_SHAPE_H */
