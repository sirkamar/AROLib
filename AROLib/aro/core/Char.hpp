#ifndef CORE_CHAR_H
#define CORE_CHAR_H

#include <aro/core/String.hpp>

namespace aro {

class Char;
typedef Ref<Char> RChar;

class Char final extends public Object implements public Comparable<Char>, public io::Streamable<Char>
{
   public:
      static const vint BYTE_SIZE;
      static const vint MAX_RADIX;
      static const vint MIN_RADIX;
      static const vchar MAX_VALUE;
      static const vchar MIN_VALUE;
      
      Char(vchar c);
      
	  virtual vint hashCode();
      virtual vchar charValue();
      virtual RString toString();
      
      virtual vint compareTo(RChar ch);
      virtual vbool equals(RObject obj);
      
      static vint hashCode(vchar c);
      static RChar valueOf(vchar c);
      static RString toString(vchar c);
      
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
      Char(); // required by Streamable
      
      const vchar value;
      
      class CharCache final extends public Object
      {
         public:
            CharCache();
            
            RArray<Char> cache;
	  };

	  static const Ref<CharCache> charCache;
   
   friend interface io::Streamable<Char>;
};

} /* namespace aro */

#endif /* CORE_CHAR_H */
