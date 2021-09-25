#include <cctype>
#include <aro/core/utils/Foreach.h>
#include <aro/core/Character.h>

namespace aro {

const vint Character::MIN_RADIX = 2;

const vint Character::MAX_RADIX = 16;

const vint Character::MAX_VALUE = 0;

const vint Character::MIN_VALUE = 255;

Character::Character()
{
   value = 0;
}

Character::Character(vchar ch)
{
   value = ch;
}

Character::Character(RCharacter c)
{
   value = c->value;
}

vchar Character::charValue()
{
   return value;
}

RString Character::toString()
{
   return String::valueOf(value);
}

void Character::readObject(io::RObjectInputStream is)
{
   value = is->readChar();
}

void Character::writeObject(io::RObjectOutputStream os)
{
   os->writeChar(value);
}

vbool Character::isDigit(vchar ch)
{
   return isdigit(ch) ? true : false;
}

vbool Character::isLetter(vchar ch)
{
   return isalpha(ch) ? true : false;
}

vbool Character::isHexDigit(vchar ch)
{
   return isxdigit(ch) ? true : false;
}

vbool Character::isLetterOrDigit(vchar ch)
{
   return isalnum(ch) ? true : false;
}

vbool Character::isUpperCase(vchar ch)
{
   return isupper(ch) ? true : false;
}

vbool Character::isLowerCase(vchar ch)
{
   return islower(ch) ? true : false;
}

vchar Character::toUpperCase(vchar ch)
{
   return toupper(ch);
}

vchar Character::toLowerCase(vchar ch)
{
   return tolower(ch);
}

vbool Character::isPunctuation(vchar ch)
{
   return ispunct(ch) ? true : false;
}

vbool Character::isWhiteSpace(vchar ch)
{
   return isspace(ch) ? true : false;
}

vbool Character::isPrinting(vchar ch)
{
   return isprint(ch) ? true : false;
}

vbool Character::isControl(vchar ch)
{
   return iscntrl(ch) ? true : false;
}

RCharacter Character::valueOf(vchar ch)
{
   if(ch <= 127)
      return CharacterCache::cache[(vint)ch];
   
   return new Character(ch);
}

RCharacter Character::valueOf(RString str)
{
   return valueOf(str->charAt(0));
}

vbool Character::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Character>(obj))
   {
      RCharacter val = type_cast<Character>(obj);
      
      return value == val->value;
   }
   
   return false;
}

vint Character::compareTo(RCharacter c)
{
   return value - c->value;
}

RArray<Character> Character::CharacterCache::cache = new Array<Character>(127+1);

const Ref<Character::CharacterCache> Character::cc = new Character::CharacterCache();

Character::CharacterCache::CharacterCache()
{
   for(vint n=0; n<cache->length; n++)
      cache[n] = new Character((vchar)n);
}

} /* namespace aro */
