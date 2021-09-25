#include <aro/core.h>
#include <aro/aws/Dimension.h>

namespace aro {

namespace aws {

Dimension::Dimension()
{
   setSize(0,0);
}

Dimension::Dimension(RDimension d)
{
   setSize(d->width, d->height);
}

Dimension::Dimension(vint width, vint height)
{
   setSize(width, height);
}

RString Dimension::toString()
{
   return "[Width: " + String::valueOf(width) +
      " Height: " + String::valueOf(height) + "]";
}

vbool Dimension::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Dimension>(obj))
   {
      RDimension d = type_cast<Dimension>(obj);
      
      return d->width == width && d->height == height;
   }
   
   return false;
}

void Dimension::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(width);
   os->writeInt(height);
}

void Dimension::readObject(io::RObjectInputStream is)
{
   width = is->readInt();
   height = is->readInt();
}

void Dimension::setSize(vint width, vint height)
{
   setWidth(width); setHeight(height);
}

void Dimension::setSize(RDimension d)
{
   setSize(d->width, d->height);
}

void Dimension::setHeight(vint height)
{
   thisref->height = height;
}

void Dimension::setWidth(vint width)
{
   thisref->width = width;
}

vint Dimension::getHeight()
{
   return height;
}

vint Dimension::getWidth()
{
   return width;
}

} /* namespace aws */

} /* namespace aro */
