#include <aro/core/Int.hpp>
#include <aro/core/Short.hpp>
#include <aro/core/impl/All.hpp>

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

Short::Short(RString str)
    :value(parse(str, 10))
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
   return Int::toString(static_cast<vint>(value));
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

RString Short::toString(vshort val, vint radix)
{
	return Int::toString(static_cast<vint>(val), radix);
}

RShort Short::valueOf(RString str, vint radix)
{
	return valueOf(parse(str, radix));
}

RString Short::toString(vshort val)
{
	return Int::toString(static_cast<vint>(val), 10);
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
    vint shAsInt = sh;
    if(shAsInt >= -128 && shAsInt <= 127)
      return shortCache->cache[shAsInt + 128];
   
	return new Short(sh);
}

RShort Short::valueOf(RString str)
{
   return valueOf(str, 10);
}

vshort Short::parse(RString str)
{
   return parse(str, 10);
}

vshort Short::parse(RString str, vint radix)
{
   vint val = Int::parse(str, radix);
   
   if(val < MIN_VALUE || val > MAX_VALUE)
	   ex_throw new ArgumentException("short value out of range. Value:\""
           + str + "\" Radix:" + String::valueOf(radix));
   
   return static_cast<vshort>(val);
}

Short::ShortCache::ShortCache()
{
   cache = new Array<Short>(-(-128) + 127 + 1);
   
   for(vint i = 0; i < cache->length; i++)
   {
      cache[i] = new Short(static_cast<vshort>(i - 128));
   }
}

const Ref<Short::ShortCache> Short::shortCache = new Short::ShortCache();

} /* namespace aro */
