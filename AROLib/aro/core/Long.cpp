#include <aro/core/Int.hpp>
#include <aro/core/Char.hpp>
#include <aro/core/Long.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

const vint Long::BYTE_SIZE = 8; // 8 bytes = 64 bits

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

Long::Long(RString str)
   :value(parse(str, 10))
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
   return toString(value);
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
   if(val >= -128L && val <= 127L)
      return longCache->cache[static_cast<vint>(val + 128L)];
   
   return new Long(val);
}

vlong Long::parse(RString str, vint radix)
{
    /*
     * WARNING: This function may be invoked early during system initialization
     * before LongCache is initialized. Care must be taken to not use
     * the Long::valueOf function.
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

    vlong result = 0;
    vbool negative = false;
    vint i = 0, len = str->length();
    vlong limit = -Long::MAX_VALUE;
    vlong multmin;
    vint digit;

    if (len > 0) {
        vchar firstChar = str->charAt(0);
        if (firstChar < '0') { // Possible leading "+" or "-"
            if (firstChar == '-') {
                negative = true;
                limit = Long::MIN_VALUE;
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

RString Long::toString(vlong i)
{
   if(i == Long::MIN_VALUE)
      return "-9223372036854775808";
   vint size = (i < 0) ? stringSize(-i) + 1 : stringSize(i);
   RArray<vchar> buf = new Array<vchar>(size);
   getChars(i, size, buf);
   return new String(buf, true);
}

RLong Long::valueOf(RString str)
{
   return valueOf(parse(str, 10));
}

vlong Long::parse(RString str)
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
   
   return wcstoll(&ch[0], nullptr, 0);*/
   return parse(str, 10);
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

RString Long::toString(vlong i, vint radix)
{
    if (radix < Char::MIN_RADIX || radix > Char::MAX_RADIX)
        radix = 10;
    if (radix == 10)
        return toString(i);
    RArray<vchar> buf = new Array<vchar>(65);
    vint charPos = 64;
    vbool negative = (i < 0);

    if (!negative) {
        i = -i;
    }

    while (i <= -radix) {
        buf[charPos--] = Int::digits[(int)(-(i % radix))];
        i = i / radix;
    }
    buf[charPos] = Int::digits[(int)(-i)];

    if (negative) {
        buf[--charPos] = '-';
    }

    return new String(buf, charPos, (65 - charPos));

}

RLong Long::valueOf(RString str, vint radix)
{
	return valueOf(parse(str, radix));
}

vint Long::stringSize(vlong val)
{
    vlong p = 10;
    for (vint i = 1; i < 19; i++) {
        if (val < p)
            return i;
        p = 10 * p;
    }
    return 19;
}

void Long::getChars(vlong val, vint index, RArray<vchar> buf)
{
    vlong q;
    vint r;
    vint charPos = index;
    vchar sign = 0;

    if (val < 0) {
        sign = '-';
        val = -val;
    }

    // Get 2 digits/iteration using longs until quotient fits into an int
    while (val > Int::MAX_VALUE) {
        q = val / 100;
        // really: r = val - (q * 100);
        r = (int)(val - ((q << 6) + (q << 5) + (q << 2)));
        val = q;
        buf[--charPos] = Int::digitOnes[r];
        buf[--charPos] = Int::digitTens[r];
    }

    // Get 2 digits/iteration using ints
    vint q2;
    vint i2 = (int)val;
    while (i2 >= 65536) {
        q2 = i2 / 100;
        // really: r = i2 - (q * 100);
        r = i2 - ((q2 << 6) + (q2 << 5) + (q2 << 2));
        i2 = q2;
        buf[--charPos] = Int::digitOnes[r];
        buf[--charPos] = Int::digitTens[r];
    }

    // Fall thru to fast mode for smaller numbers
    // assert(i2 <= 65536, i2);
    for (;;) {
        q2 = urShift((i2 * 52429), (16 + 3));
        r = i2 - ((q2 << 3) + (q2 << 1));  // r = i2-(q2*10) ...
        buf[--charPos] = Int::digits[r];
        i2 = q2;
        if (i2 == 0) break;
    }
    if (sign != 0) {
        buf[--charPos] = sign;
    }
}

Long::LongCache::LongCache()
{
    cache = new Array<Long>(-(-128) + 127 + 1);

    for (vint i = 0; i < cache->length; i++)
    {
        cache[i] = new Long(i - 128);
    }
}

const Ref<Long::LongCache> Long::longCache = new Long::LongCache();

} /* namespace aro */
