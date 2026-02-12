#include <aro/core/Int.hpp>
#include <aro/core/Char.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

const vint Int::BYTE_SIZE = 4; // 4 bytes = 32 bits

const vint Int::MAX_VALUE = 0x7fffffff; // (2^31)-1

const vint Int::MIN_VALUE = 0x80000000; // (-2)^31

const RArray<vchar> Int::digits = {
    '0' , '1' , '2' , '3' , '4' , '5' ,
    '6' , '7' , '8' , '9' , 'a' , 'b' ,
    'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
    'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
    'o' , 'p' , 'q' , 'r' , 's' , 't' ,
    'u' , 'v' , 'w' , 'x' , 'y' , 'z'
};

const RArray<vchar> Int::digitTens = {
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
    '2', '2', '2', '2', '2', '2', '2', '2', '2', '2',
    '3', '3', '3', '3', '3', '3', '3', '3', '3', '3',
    '4', '4', '4', '4', '4', '4', '4', '4', '4', '4',
    '5', '5', '5', '5', '5', '5', '5', '5', '5', '5',
    '6', '6', '6', '6', '6', '6', '6', '6', '6', '6',
    '7', '7', '7', '7', '7', '7', '7', '7', '7', '7',
    '8', '8', '8', '8', '8', '8', '8', '8', '8', '8',
    '9', '9', '9', '9', '9', '9', '9', '9', '9', '9',
};

const RArray<vchar> Int::digitOnes = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
};


const RArray<vint> Int::sizeTable = { 9, 99, 999, 9999, 99999, 999999, 9999999,
                                      99999999, 999999999, Int::MAX_VALUE };

Int::Int()
   :value(0)
{
   
}

Int::Int(vint val)
   :value(val)
{
   
}

Int::Int(RString str)
   :value(parse(str, 10))
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
   if(val >= IntCache::low && val <= IntCache::high)
       return intCache->cache[val + (-IntCache::low)];
   
   return new Int(val);
}

RInt Int::valueOf(RString str)
{
   return valueOf(parse(str, 10));
}

RString Int::toString(vint val)
{
   if(val == Int::MIN_VALUE)
      return "-2147483648";
   
   vint size = (val < 0) ? stringSize(-val) + 1 : stringSize(val);
   RArray<vchar> buf = new Array<vchar>(size);
   getChars(val, size, buf);
   return new String(buf, true);
}

RString Int::toString(vint i, vint radix)
{
    if (radix < Char::MIN_RADIX || radix > Char::MAX_RADIX)
        radix = 10;

    /* Use the faster version */
    if (radix == 10) {
        return toString(i);
    }

    RArray<vchar> buf = new Array<vchar>(33);
    vbool negative = (i < 0);
    vint charPos = 32;

    if (!negative) {
        i = -i;
    }

    while (i <= -radix) {
        buf[charPos--] = digits[-(i % radix)];
        i = i / radix;
    }
    buf[charPos] = digits[-i];

    if (negative) {
        buf[--charPos] = '-';
    }

    return new String(buf, charPos, (33 - charPos));
}

RInt Int::valueOf(RString str, vint radix)
{
   return valueOf(parse(str, radix));
}

vint Int::parse(RString str, vint radix)
{
    /*
     * WARNING: This function may be invoked early during system initialization
     * before IntCache is initialized. Care must be taken to not use
     * the Int::valueOf function.
     */

    if (str == nullref) {
        ex_throw new ArgumentException("Number format error: null");
    }

    if (radix < Char::MIN_RADIX) {
        ex_throw new ArgumentException("Number format error: radix " + String::valueOf(radix) +
            " less than Char::MIN_RADIX");
    }

    if (radix > Char::MAX_RADIX) {
        ex_throw new ArgumentException("Number format error: radix " + String::valueOf(radix) +
            " greater than Char::MAX_RADIX");
    }

    vint result = 0;
    vbool negative = false;
    vint i = 0, len = str->length();
    vint limit = -Int::MAX_VALUE;
    vint multmin;
    vint digit;

    if (len > 0) {
        vchar firstChar = str->charAt(0);
        if (firstChar < '0') { // Possible leading "+" or "-"
            if (firstChar == '-') {
                negative = true;
                limit = Int::MIN_VALUE;
            }
            else if (firstChar != '+')
                ex_throw new ArgumentException("Number format error for Input String: " + str);

            if (len == 1) // Cannot have lone "+" or "-"
                ex_throw new ArgumentException("Number format error for Input String: " + str);
            i++;
        }
        multmin = limit / radix;
        while (i < len) {
            // Accumulating negatively avoids surprises near MAX_VALUE
            digit = Int::toDigit(str->charAt(i++), radix);
            if (digit < 0) {
                ex_throw new ArgumentException("Number format error for Input String: " + str);
            }
            if (result < multmin) {
                ex_throw new ArgumentException("Number format error for Input String: " + str);
            }
            result *= radix;
            if (result < limit + digit) {
                ex_throw new ArgumentException("Number format error for Input String: " + str);
            }
            result -= digit;
        }
    }
    else {
        ex_throw new ArgumentException("Number format error for Input String: " + str);
    }
    return negative ? result : -result;
}

vint Int::parse(RString str)
{
   /*vint offset = 0;
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
   
   return wcstol(&ch[0], nullptr, 0);*/
   return parse(str, 10);
}

vint Int::toDigit(vchar c, vint radix)
{
   if(c >= '0' && c <= '9')
      return (c - '0' < radix) ? (c - '0') : -1;
   
   if(c >= 'a' && c <= 'z')
      return (c - 'a' + 10 < radix) ? (c - 'a' + 10) : -1;
   
   if(c >= 'A' && c <= 'Z')
      return (c - 'A' + 10 < radix) ? (c - 'A' + 10) : -1;
   
   return -1;
}

vint Int::stringSize(vint val)
{
   for (int i = 0; ; i++)
      if (val <= sizeTable[i])
         return i + 1;
}

void Int::getChars(vint val, vint index, RArray<vchar> buf)
{
    vint q, r;
    vint charPos = index;
    vchar sign = 0;

    if (val < 0) {
        sign = '-';
        val = -val;
    }

    // Generate two digits per iteration
    while (val >= 65536) {
        q = val / 100;
        // really: r = val - (q * 100);
        r = val - ((q << 6) + (q << 5) + (q << 2));
        val = q;
        buf[--charPos] = digitOnes[r];
        buf[--charPos] = digitTens[r];
    }

    // Fall thru to fast mode for smaller numbers
    // assert(val <= 65536, val);
    for (;;) {
        q = urShift((val * 52429), (16 + 3));
        r = val - ((q << 3) + (q << 1));  // r = val-(q*10) ...
        buf[--charPos] = digits[r];
        val = q;
        if (val == 0) break;
    }
    if (sign != 0) {
        buf[--charPos] = sign;
    }
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

Int::IntCache::IntCache()
{
    cache = new Array<Int>((high - low) + 1);

    for (vint i = 0, j = low; i < cache->length; i++)
    {
        cache[i] = new Int(j++);
    }
}

const vint Int::IntCache::low = -128;

const vint Int::IntCache::high = 127;

const Ref<Int::IntCache> Int::intCache = new Int::IntCache();

} /* namespace aro */
