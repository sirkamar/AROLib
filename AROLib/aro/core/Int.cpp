#include <cstdlib>
#include <aro/core/Int.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

const vint Int::MAX_VALUE = 0x7fffffff; // (2^31)-1

const vint Int::MIN_VALUE = 0x80000000; // (-2)^31

Int::Int()
   :value(0)
{
   
}

Int::Int(vint val)
   :value(val)
{
   
}

Int::Int(RInt val)
   :value(val->value)
{
   
}

vint Int::hashCode()
{
   return value;
}

vint Int::intValue()
{
   return value;
}

vlong Int::longValue()
{
   return static_cast<vlong>(value);
}

vfloat Int::floatValue()
{
   return static_cast<vfloat>(value);
}

vdouble Int::doubleValue()
{
   return static_cast<vdouble>(value);
}

RString Int::toString()
{
   return String::valueOf(value);
}

vint Int::compareTo(RInt num)
{
   vint val = num->value;
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

vbool Int::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Int>(obj))
   {
      RInt val = type_cast<Int>(obj);
      
      return (value == val->value);
   }
   
   return false;
}

void Int::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vint&>(value) = is->readInt();
}

void Int::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(value);
}

RInt Int::valueOf(vint val)
{
   return new Int(val);
}

RInt Int::valueOf(RString str)
{
   return valueOf(parse(str));
}

vint Int::parse(RString str)
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
   
   return wcstol(&ch[0], nullptr, 0);
}

vint Int::urShift(vint val, vint n)
{
   vint mask = 1 << 31;

   for(vint i=0; i<n; i++)
   {
      val >>= 1;

      if(val < 0)
         val ^= mask;
   }

   return val;
}

} /* namespace aro */
