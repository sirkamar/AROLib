#include <bitset>
#include <cstdlib>
#include <aro/core/Decimal.h>
#include <aro/core/utils/Foreach.h>

namespace aro {

const vdouble Decimal::MAX_VALUE = 1.7976931348623157E+308;

//const vdouble Decimal::NEGATIVE_INFINITY = -1.0 / 0.0;

//const vdouble Decimal::POSITIVE_INFINITY = 1.0 / 0.0;

const vdouble Decimal::MIN_VALUE = 4.9E-324;

const vdouble Decimal::MIN_EXPONENT = -1022;

const vdouble Decimal::MAX_EXPONENT = 1023;

//const vdouble Decimal::NaN = 0.0 / 0.0;

Decimal::Decimal()
{
   value = 0.0;
}

Decimal::Decimal(vdouble val)
{
   value = val;
}

Decimal::Decimal(RDecimal val)
{
   value = val->value;
}

vint Decimal::intValue()
{
   return (vint) value;
}

vlong Decimal::longValue()
{
   return (vlong) value;
}

vfloat Decimal::floatValue()
{
   return (vfloat) value;
}

vdouble Decimal::doubleValue()
{
   return value;
}

RString Decimal::toString()
{
   return String::valueOf(value);
}

vbool Decimal::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Decimal>(obj))
   {
      RDecimal val = type_cast<Decimal>(obj);
      
      return !(value < val->value || value > val->value);
   }
   
   return false;
}

vint Decimal::compareTo(RDecimal num)
{
   vdouble val = num->doubleValue();
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

void Decimal::readObject(io::RObjectInputStream is)
{
   value = is->readDouble();
}

void Decimal::writeObject(io::RObjectOutputStream os)
{
   os->writeDouble(value);
}

vdouble Decimal::longBitsToDouble(vlong bits)
{
   vdouble result;
   
   std::bitset<64> buf = bits;
   
   *((vlong*)&result) = buf.to_ulong();
   
   return result;
}

vlong Decimal::doubleToLongBits(vdouble val)
{
   std::bitset<64> bits = *(vlong*)&val;
   
   return (vlong) bits.to_ulong();
}

vfloat Decimal::intBitsToFloat(vint bits)
{
   vfloat result;
   
   std::bitset<32> buf = bits;
   
   *((vint*)&result) = buf.to_ulong();
   
   return result;
}

vint Decimal::floatToIntBits(vfloat val)
{
   std::bitset<32> bits = *(vint*)&val;
   
   return (vint) bits.to_ulong();
}

RDecimal Decimal::valueOf(vdouble val)
{
   return new Decimal(val);
}

RDecimal Decimal::valueOf(RString str)
{
   return valueOf(parse(str));
}

vdouble Decimal::parse(RString str)
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
