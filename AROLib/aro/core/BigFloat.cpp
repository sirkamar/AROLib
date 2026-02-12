#include <bitset>
#include <cstdlib>
#include <aro/core/BigFloat.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

const vdouble BigFloat::MAX_VALUE = 1.7976931348623157E+308;

//const vdouble BigFloat::NEGATIVE_INFINITY = -1.0 / 0.0;

//const vdouble BigFloat::POSITIVE_INFINITY = 1.0 / 0.0;

const vdouble BigFloat::MIN_VALUE = 4.9E-324;

const vdouble BigFloat::MIN_EXPONENT = -1022;

const vdouble BigFloat::MAX_EXPONENT = 1023;

//const vdouble BigFloat::NaN = 0.0 / 0.0;

BigFloat::BigFloat()
{
   value = 0.0;
}

BigFloat::BigFloat(vdouble val)
{
   value = val;
}

BigFloat::BigFloat(RBigFloat val)
{
   value = val->value;
}

vint BigFloat::intValue()
{
   return (vint) value;
}

vlong BigFloat::longValue()
{
   return (vlong) value;
}

vfloat BigFloat::floatValue()
{
   return (vfloat) value;
}

vdouble BigFloat::doubleValue()
{
   return value;
}

RString BigFloat::toString()
{
   return String::valueOf(value);
}

vbool BigFloat::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<BigFloat>(obj))
   {
      RBigFloat val = type_cast<BigFloat>(obj);
      
      return !(value < val->value || value > val->value);
   }
   
   return false;
}

vint BigFloat::compareTo(RBigFloat num)
{
   vdouble val = num->doubleValue();
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

void BigFloat::readObject(io::RObjectInputStream is)
{
   value = is->readDouble();
}

void BigFloat::writeObject(io::RObjectOutputStream os)
{
   os->writeDouble(value);
}

vdouble BigFloat::longBitsToDouble(vlong bits)
{
   vdouble result;
   
   std::bitset<64> buf = bits;
   
   *((vlong*)&result) = buf.to_ulong();
   
   return result;
}

vlong BigFloat::doubleToLongBits(vdouble val)
{
   std::bitset<64> bits = *(vlong*)&val;
   
   return (vlong) bits.to_ulong();
}

vfloat BigFloat::intBitsToFloat(vint bits)
{
   vfloat result;
   
   std::bitset<32> buf = bits;
   
   *((vint*)&result) = buf.to_ulong();
   
   return result;
}

vint BigFloat::floatToIntBits(vfloat val)
{
   std::bitset<32> bits = *(vint*)&val;
   
   return (vint) bits.to_ulong();
}

RBigFloat BigFloat::valueOf(vdouble val)
{
   return new BigFloat(val);
}

RBigFloat BigFloat::valueOf(RString str)
{
   return valueOf(parse(str));
}

vdouble BigFloat::parse(RString str)
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
   
   return wcstod(&ch[0], nullptr);
}

} /* namespace aro */
