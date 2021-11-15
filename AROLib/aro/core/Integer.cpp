#include <cstdlib>
#include <aro/core/Integer.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

const vint Integer::INT_MAX_VALUE = 0x7fffffff; // 2^31-1

const vint Integer::INT_MIN_VALUE = 0x80000000; // -2^31

Integer::Integer()
   :value(0)
{
   //value = 0;
}

Integer::Integer(vint val)
   :value(val)
{
   //value = val;
}

Integer::Integer(RInteger val)
   :value(val->value)
{
   //value = val->value;
}

vint Integer::intValue()
{
   return value;
}

vlong Integer::longValue()
{
   return (vlong) value;
}

vfloat Integer::floatValue()
{
   return (vfloat) value;
}

vdouble Integer::doubleValue()
{
   return (vdouble) value;
}

RString Integer::toString()
{
   return String::valueOf(value);
}

vint Integer::compareTo(RInteger num)
{
   vint val = num->value;
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

vbool Integer::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Integer>(obj))
   {
      RInteger val = type_cast<Integer>(obj);
      
      return (value == val->value);
   }
   
   return false;
}

void Integer::readObject(io::RObjectInputStream is)
{
   const_cast<vint&>(value) = is->readInt();
}

void Integer::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(value);
}

RInteger Integer::valueOf(vlong val)
{
   return new Integer(val);
}

RInteger Integer::valueOf(RString str)
{
   return valueOf(parse(str));
}

vint Integer::parse(RString str)
{
   vint offset = 0;
   vint len = str->length();
   RArray<vchar> ch = new Array<vchar>(len+1);
   str->getChars(0, len, ch, 0); ch[len] = '\0';
   
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
   
   return wcstol(&ch[0], nullptr, 0);
}

vint Integer::urShift(vint val, vint n)
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

vlong Integer::urShift(vlong val, vint n)
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
