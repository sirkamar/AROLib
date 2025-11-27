#ifndef CORE_CHARACTER_H
#define CORE_CHARACTER_H

#include <aro/core/String.hpp>

namespace aro {

class Character;
typedef Ref<Character> RCharacter;

class Character final extends public Object implements public Comparable<Character>, public Cloneable<Character>, public io::Streamable<Character>
{
   public:
      static const vint MIN_RADIX;
      static const vint MAX_RADIX;
      static const vint MAX_VALUE;
      static const vint MIN_VALUE;
      
      Character();
      Character(vchar c);
      Character(RCharacter ch);
      
      vchar charValue();
      virtual RString toString();
      
      virtual vint compareTo(RCharacter ch);
      virtual vbool equals(RObject obj);
      
      static RCharacter valueOf(vchar c);
      static RCharacter valueOf(RString str);
      
      static vbool isLetterOrDigit(vchar c);
      static vbool isHexDigit(vchar c);
      static vbool isLetter(vchar c);
      static vbool isDigit(vchar c);
      
      static vbool isLowerCase(vchar c);
      static vbool isUpperCase(vchar c);
      static vchar toLowerCase(vchar c);
      static vchar toUpperCase(vchar c);
      
      static vbool isPunctuation(vchar c);
      static vbool isWhiteSpace(vchar c);
      static vbool isPrinting(vchar c);
      static vbool isControl(vchar c);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      vchar value;
      
      class CharacterCache : public Object
      {
         public:
            static RArray<Character> cache;
            
            CharacterCache();
      };
      
      static const Ref<CharacterCache> cc;
};

} /* namespace aro */

#endif /* CORE_CHARACTER_H */
