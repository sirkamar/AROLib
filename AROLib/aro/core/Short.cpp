#include <aro/core/Int.hpp>
#include <aro/core/Short.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

const vshort Short::MIN_VALUE = -32768;

const vshort Short::MAX_VALUE = 32767;

Short::Short()
   :value(0)
{
   
}

Short::Short(vshort val)
   :value(val)
{
   
}

Short::Short(RShort val)
   :value(val->value)
{
   
}

vint Short::intValue()
{
   return static_cast<vint>(value);
}

vlong Short::longValue()
{
   return static_cast<vlong>(value);
}

vshort Short::shortValue()
{
   return value;
}

vfloat Short::floatValue()
{
   return static_cast<vfloat>(value);
}

vdouble Short::doubleValue()
{
   return static_cast<vdouble>(value);
}

vint Short::hashCode()
{
   return static_cast<vint>(value);
}

RString Short::toString()
{
   return String::valueOf(value);
}

vbool Short::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Short>(obj))
   {
      RShort val = type_cast<Short>(obj);
      
      return value == val->value;
   }
   
   return false;
}

vint Short::compareTo(RShort val)
{
   return value - val->value;
}

void Short::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vshort&>(value) = is->readShort();
}

void Short::writeObject(io::RObjectOutputStream os)
{
   os->writeShort(value);
}

RShort Short::valueOf(vshort sh)
{
   return new Short(sh);
}

RShort Short::valueOf(RString str)
{
   return valueOf(parse(str));
}

vshort Short::parse(RString str)
{
   vint val = Int::parse(str);
   
   if(val < MIN_VALUE || val > MAX_VALUE)
	   ex_throw new ArgumentException("short value out of range: \"" + str + "\"");
   
   return static_cast<vshort>(val);
}

} /* namespace aro */
