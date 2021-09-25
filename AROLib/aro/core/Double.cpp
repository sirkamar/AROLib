#include <bitset>
#include <cstdlib>
#include <aro/core/Long.h>
#include <aro/core/Double.h>
#include <aro/core/utils/Foreach.h>

namespace aro {

const vdouble Double::MAX_VALUE = 1.7976931348623157E+308;

//const vdouble Double::NEGATIVE_INFINITY = -1.0 / 0.0;

//const vdouble Double::POSITIVE_INFINITY = 1.0 / 0.0;

const vdouble Double::MIN_VALUE = 4.9E-324;

const vdouble Double::MIN_EXPONENT = -1022;

const vdouble Double::MAX_EXPONENT = 1023;

//const vdouble Double::NaN = 0.0 / 0.0;

Double::Double()
   :value(0)
{
   
}

Double::Double(vdouble val)
   :value(val)
{
   
}

Double::Double(RDouble val)
   :value(val->value)
{
   
}

vint Double::hashCode()
{
   vlong bits = doubleToLongBits(value);

   bits = (bits ^ (Long::urShift(bits, 16)));

   return static_cast<vint>(bits);

   //return (vint) (bits ^ (bits >>> 32));
}

vint Double::intValue()
{
   return static_cast<vint>(value);
}

vlong Double::longValue()
{
   return static_cast<vlong>(value);
}

vfloat Double::floatValue()
{
   return static_cast<vfloat>(value);
}

vdouble Double::doubleValue()
{
   return value;
}

RString Double::toString()
{
   return String::valueOf(value);
}

vbool Double::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Double>(obj))
   {
      RDouble val = type_cast<Double>(obj);
      
      return !(value < val->value || value > val->value);
   }
   
   return false;
}

vint Double::compareTo(RDouble num)
{
   vdouble val = num->doubleValue();
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

void Double::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vdouble&>(value) = is->readDouble();
}

void Double::writeObject(io::RObjectOutputStream os)
{
   os->writeDouble(value);
}

vdouble Double::longBitsToDouble(vlong bits)
{
   vdouble result;
   
   std::bitset<64> buf = bits;
   
   *((vlong*)&result) = buf.to_ullong();
   
   return result;
}

vlong Double::doubleToLongBits(vdouble val)
{
   // casting val itself may cause truncation
   // so instead we cast the address then
   // we dereference its bit sequence.
   std::bitset<64> bits = *(vlong*)&val;
   
   return bits.to_ullong();
}

RDouble Double::valueOf(vdouble val)
{
   return new Double(val);
}

RDouble Double::valueOf(RString str)
{
   return valueOf(parse(str));
}

vdouble Double::parse(RString str)
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
   
   // should now be at numeric part of the significand
   vint dotoff = -1;                 // '.' offset, -1 if none
   vlong exp = 0;                    // exponent
   
   for(; len>0; offset++, len--)
   {
      vchar c = ch[offset];
      if(c >= '0' && c <= '9')  // have digit
         continue;
         
      if(c == '.') // have dot
      {
         if(dotoff >= 0)         // two dots
            ex_throw new ArgumentException("Invalid number format");
         
         dotoff = offset;
         continue;
      }
      
      if((c != 'e') && (c != 'E')) // exponent expected
         ex_throw new ArgumentException("Invalid number format");
      
      offset++;
      c = ch[offset];
      len--;
      vbool negexp = false;
      
      if(c == '-' || c == '+') // optional sign
      {
         negexp = (c == '-');
         offset++;
         c = ch[offset];
         len--;
      }
      
      if(len <= 0)    // no exponent digits
         ex_throw new ArgumentException("Invalid number format");
      
      // skip leading zeros in the exponent 
      while(len > 3 && c == '0')
      {
         offset++;
         c = ch[offset];
         len--;
      }
      
      if(len > 3)  // too many nonzero exponent digits
         ex_throw new ArgumentException("Invalid number format");
      
      // c now holds first digit of exponent
      for(;; len--)
      {
         vint v;
         if(c >= '0' && c <= '9')
         {
            v = c - '0';
         }
         else
         {
            v = c;
            if(v < '0')            // not a digit
               ex_throw new ArgumentException("Invalid number format");
         }
         exp = exp * 10 + v;
         if(len == 1)
            break;               // that was final character
         offset++;
         c = ch[offset];
      }
      if(negexp)                  // apply sign
         exp = -exp;

      // Next test is required for backwards compatibility
      if((vint)exp != exp)         // overflow
         ex_throw new ArgumentException("Invalid number format");

      break;                       // [saves a test]
   }
   
   ch[len] = '\0';
   
   return wcstod(&ch[0], nullptr);
}

} /* namespace aro */
