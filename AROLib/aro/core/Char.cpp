#include <cctype>
#include <aro/core/Char.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

const vint Char::BYTE_SIZE = 2; // 2 bytes = 16 bits

const vint Char::MAX_RADIX = 36;

const vint Char::MIN_RADIX = 2;

const vchar Char::MAX_VALUE = L'\uFFFF'; // 127

const vchar Char::MIN_VALUE = L'\u0000'; // 0

Char::Char()
   :Char(0)
{
   
}

Char::Char(vchar ch)
   :value(ch)
{
   
}

vint Char::hashCode()
{
   return static_cast<vint>(value);
}

vchar Char::charValue()
{
   return value;
}

RString Char::toString()
{
   return String::valueOf(value);
}

vint Char::compareTo(RChar c)
{
   return value - c->value;
}

vbool Char::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Char>(obj))
   {
      RChar val = type_cast<Char>(obj);
      
      return value == val->value;
   }
   
   return false;
}

void Char::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vchar&>(value) = is->readChar();
}

void Char::writeObject(io::RObjectOutputStream os)
{
   os->writeChar(value);
}

vint Char::hashCode(vchar ch)
{
   return static_cast<vint>(ch);
}

RChar Char::valueOf(vchar ch)
{
   if (ch <= MAX_VALUE)
      return charCache->cache[static_cast<vint>(ch)];
   
   return new Char(ch);
}

RString Char::toString(vchar ch)
{
   return String::valueOf(ch);
}

vbool Char::isDigit(vchar ch)
{
   return isdigit(ch) ? true : false;
}

vbool Char::isLetter(vchar ch)
{
   return isalpha(ch) ? true : false;
}

vbool Char::isHexDigit(vchar ch)
{
   return isxdigit(ch) ? true : false;
}

vbool Char::isLetterOrDigit(vchar ch)
{
   return isalnum(ch) ? true : false;
}

vbool Char::isUpperCase(vchar ch)
{
   return isupper(ch) ? true : false;
}

vbool Char::isLowerCase(vchar ch)
{
   return islower(ch) ? true : false;
}

vchar Char::toUpperCase(vchar ch)
{
   return toupper(ch);
}

vchar Char::toLowerCase(vchar ch)
{
   return tolower(ch);
}

vbool Char::isPunctuation(vchar ch)
{
   return ispunct(ch) ? true : false;
}

vbool Char::isWhiteSpace(vchar ch)
{
   return isspace(ch) ? true : false;
}

vbool Char::isPrinting(vchar ch)
{
   return isprint(ch) ? true : false;
}

vbool Char::isControl(vchar ch)
{
   return iscntrl(ch) ? true : false;
}

Char::CharCache::CharCache()
{
   cache = new Array<Char>(MAX_VALUE + 1);

   for(vint i=MIN_VALUE; i<=MAX_VALUE; i++)
   {
      cache[i] = new Char(static_cast<vchar>(i));
   }
}

const Ref<Char::CharCache> Char::charCache = new Char::CharCache();

} /* namespace aro */
