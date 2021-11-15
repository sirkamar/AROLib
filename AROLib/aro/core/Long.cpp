#include <cstdlib>
#include <aro/core/Int.hpp>
#include <aro/core/Long.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

const vlong Long::MAX_VALUE = 0x7fffffffffffffffL; //2^63-1

const vlong Long::MIN_VALUE = 0x8000000000000000L; //-2^63

Long::Long()
   :value(0L)
{
   
}

Long::Long(vlong val)
   :value(val)
{
   
}

Long::Long(RLong val)
   :value(val->value)
{
   
}

vint Long::hashCode()
{
   vlong val = value ^ urShift(value, 32);
   
   return static_cast<vint>(val);
}

vint Long::intValue()
{
   return static_cast<vint>(value);
}

vlong Long::longValue()
{
   return value;
}

vfloat Long::floatValue()
{
   return static_cast<vfloat>(value);
}

vdouble Long::doubleValue()
{
   return static_cast<vdouble>(value);
}

RString Long::toString()
{
   return String::valueOf(value);
}

vbool Long::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Long>(obj))
   {
      RLong val = type_cast<Long>(obj);
      
      return value == val->value;
   }
   
   return false;
}

vint Long::compareTo(RLong num)
{
   vlong val = num->value;
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

void Long::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vlong&>(value) = is->readLong();
}

void Long::writeObject(io::RObjectOutputStream os)
{
   os->writeLong(value);
}

RLong Long::valueOf(vlong val)
{
   return new Long(val);
}

RLong Long::valueOf(RString str)
{
   return valueOf(parse(str));
}

vlong Long::parse(RString str)
{
   vint offset = 0;
   vint len = str->length();
   RArray<vchar> ch = new Array<vchar>(len+1);
   str->getChars(0, len, ch, 0);
   
   // handle the sign
   if(ch[offset] == '-' || ch[offset] == '+') // leading - or + allowed
   {
      offset++;
      len--;
   }
   
   for(; len>0; offset++, len--)
   {
      vchar c = ch[offset];
      if(c >= '0' && c <= '9')  // have digit
         continue;
         
      ex_throw new ArgumentException("Invalid number format");
   }
   
   ch[len] = '\0';
   
   return wcstoll(&ch[0], nullptr, 0);
}

vlong Long::urShift(vlong val, vint n)
{
   vlong mask = 1LL << 63;

   for(vint i=0; i<n; i++)
   {
      val >>= 1;

      if(val < 0LL)
         val ^= mask;
   }

   return val;
}

} /* namespace aro */
