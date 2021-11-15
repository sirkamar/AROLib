#include <cctype>
#include <aro/core/Char.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

const vint Char::MAX_VALUE = 127;

const vint Char::MIN_VALUE = 0;

Char::Char()
   :value(0)
{
   
}

Char::Char(vchar ch)
   :value(ch)
{
   
}

Char::Char(RChar c)
   :value(c->value)
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

void Char::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vchar&>(value) = is->readChar();
}

void Char::writeObject(io::RObjectOutputStream os)
{
   os->writeChar(value);
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

RChar Char::valueOf(vchar ch)
{
   return new Char(ch);
}

RChar Char::valueOf(RString str)
{
   return valueOf(str->charAt(0));
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

vint Char::compareTo(RChar c)
{
   return value - c->value;
}

} /* namespace aro */
