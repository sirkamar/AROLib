#include <bitset>
#include <cstdlib>
#include <aro/core/Float.h>
#include <aro/core/utils/Foreach.h>

namespace aro {

//const vfloat Float::NEGATIVE_INFINITY = -1.0f / 0.0f;

//const vfloat Float::POSITIVE_INFINITY = 1.0f / 0.0f;

const vfloat Float::MAX_VALUE = 3.4E+38f;

const vfloat Float::MIN_VALUE = 1.4E-45f;

const vfloat Float::MIN_EXPONENT = -126;

const vfloat Float::MAX_EXPONENT = 127;

//const vfloat Float::NaN = 0.0f / 0.0f;

Float::Float()
   :value(0.0)
{
   
}

Float::Float(vfloat val)
   :value(val)
{
   
}

Float::Float(RFloat val)
   :value(val->value)
{
   
}

vint Float::hashCode()
{
   return floatToIntBits(value);
}

vint Float::intValue()
{
   return static_cast<vint>(value);
}

vlong Float::longValue()
{
   return static_cast<vlong>(value);
}

vfloat Float::floatValue()
{
   return value;
}

vdouble Float::doubleValue()
{
   return static_cast<vdouble>(value);
}

RString Float::toString()
{
   return String::valueOf(value);
}

vbool Float::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Float>(obj))
   {
      RFloat val = type_cast<Float>(obj);
      
      return !(value < val->value || value > val->value);
   }
   
   return false;
}

vint Float::compareTo(RFloat num)
{
   vfloat val = num->value;
   
   return (value < val ? -1 : (value > val ? 1 : 0));
}

void Float::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vfloat&>(value) = is->readFloat();
}

void Float::writeObject(io::RObjectOutputStream os)
{
   os->writeFloat(value);
}

vfloat Float::intBitsToFloat(vint bits)
{
   vfloat result;
   
   std::bitset<32> buf = bits;
   
   *((vint*)&result) = buf.to_ulong();
   
   return result;
}

vint Float::floatToIntBits(vfloat val)
{
   // casting val itself may cause truncation
   // so instead we cast the address then
   // we dereference its bit sequence.
   std::bitset<32> bits = *(vint*)&val;
   
   return static_cast<vint>(bits.to_ulong());
}

RFloat Float::valueOf(vfloat val)
{
   return new Float(val);
}

RFloat Float::valueOf(RString str)
{
   return valueOf(parse(str));
}

vfloat Float::parse(RString str)
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
   
   return wcstof(&ch[0], nullptr);
}

} /* namespace aro */
