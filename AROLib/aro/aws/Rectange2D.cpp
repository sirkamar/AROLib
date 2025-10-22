#include <aro/core.h>
#include <aro/aws/Rectange2D.h>

namespace aro {

namespace aws {

Rectangle2D::Rectangle2D()
	:Rectangle2D(0.0, 0.0)
{

}

Rectangle2D::Rectangle2D(RRectangle2D rect)
	:Rectangle2D(rect->length, rect->width)
{

}

Rectangle2D::Rectangle2D(vdouble length, vdouble width)
{
	if(length < 0.0 || width < 0.0)
		ex_throw new ArgumentException("Length and Width must be non-negative");

	this->length = length;
	this->width = width;
}

void Rectangle2D::setLength(vdouble length)
{
	if(length < 0.0)
		ex_throw new ArgumentException("Length must be non-negative");

	this->length = length;
}

void Rectangle2D::setWidth(vdouble width)
{
	if(width < 0.0)
		ex_throw new ArgumentException("Width must be non-negative");

	this->width = width;
}

vdouble Rectangle2D::getLength()
{
	return this->length;
}

vdouble Rectangle2D::getWidth()
{
	return this->width;
}

vdouble Rectangle2D::getArea()
{
	return length * width;
}

vdouble Rectangle2D::getPerimeter()
{
	return 2 * (length + width);
}

vint Rectangle2D::hashCode()
{
	return Double::doubleToLongBits(length) * 31 + Double::doubleToLongBits(width) * 31;
}

RString Rectangle2D::toString()
{
	return "";
}

vbool Rectangle2D::equals(RObject obj)
{
	if (thisref == obj)
		return true;

	if (type_of<Rectangle2D>(obj))
	{
		auto rect = type_cast<Rectangle2D>(obj);

		return rect->length == length && rect->width == width;
	}

	return false;
}

void Rectangle2D::writeObject(io::RObjectOutputStream os)
{
	os->writeDouble(length);
	os->writeDouble(width);
}

void Rectangle2D::readObject(io::RObjectInputStream is)
{
	length = is->readDouble();
	width = is->readDouble();
}

} /* namespace aws */

} /* namespace aro */
