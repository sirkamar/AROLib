#include <cstdlib>
#include <aro/core/BigInt.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

const vint BigInt::INT_MAX_VALUE = 0x7fffffff; // 2^31-1

const vint BigInt::INT_MIN_VALUE = 0x80000000; // -2^31

BigInt::BigInt()
   :value(0)
{
   //value = 0;
}

BigInt::BigInt(vint val)
   :value(val)
{
   //value = val;
}

BigInt::BigInt(RBigInt val)
   :value(val->value)
{
   //value = val->value;
}

vint BigInt::intValue()
{
   return value;
}

vlong BigInt::longValue()
{
   return (vlong) value;
}

vfloat BigInt::floatValue()
{
   return (vfloat) value;
}

vdouble BigInt::doubleValue()
{
   return (vdouble) value;
}

RString BigInt::toString()
{
   return String::valueOf(value);
}

vint BigInt::compareTo(RBigInt num)
{
   vint val = num->value;
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

vbool BigInt::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<BigInt>(obj))
   {
      RBigInt val = type_cast<BigInt>(obj);
      
      return (value == val->value);
   }
   
   return false;
}

void BigInt::readObject(io::RObjectInputStream is)
{
   const_cast<vint&>(value) = is->readInt();
}

void BigInt::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(value);
}

RBigInt BigInt::valueOf(vlong val)
{
   return new BigInt(val);
}

RBigInt BigInt::valueOf(RString str)
{
   return valueOf(parse(str));
}

vint BigInt::parse(RString str)
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

vint BigInt::urShift(vint val, vint n)
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

vlong BigInt::urShift(vlong val, vint n)
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
