#ifndef CORE_STRING_H
#define CORE_STRING_H

#include <aro/core/Array2D.hpp>
#include <aro/core/Comparable.hpp>

namespace aro {

class String final : public Object, public Comparable<String>, public Cloneable<String>, public io::Streamable<String>
{
   public:
      static const RString EMPTY_STRING;
      
      String();
      String(RString str);
      String(RArray<vchar> arr);
      String(RArray<vchar> arr, vint offset, vint count);
      
      virtual vint length();
      
	  virtual vint hashCode();
      
      virtual vbool isEmpty();

      virtual RString trim();
      
      virtual RString toString();
      
      virtual RString toLowerCase();
      virtual RString toUpperCase();
      
      virtual vchar charAt(vint index);
      
      virtual vbool equals(RObject obj);
      
      virtual RArray<vchar> toCharArray();
      
      virtual vint compareTo(RString str);
      
      virtual RString concat(RString str);
      
      virtual vint indexOf(vchar ch);
      virtual vint indexOf(vchar ch,vint offset);
      
      virtual vint indexOf(RString str);
      virtual vint indexOf(RString str, vint offset);
      
      virtual vint lastIndexOf(vchar ch);
      virtual vint lastIndexOf(vchar ch,vint offset);
      
      virtual vint lastIndexOf(RString str);
      virtual vint lastIndexOf(RString str, vint offset);
      
      virtual vbool equalsIgnoreCase(RString str);
      
      virtual vint compareToIgnoreCase(RString str);
      
      virtual RString substring(vint from);
      virtual RString substring(vint from,vint end);
      
      virtual vbool endsWith(RString str);
      virtual vbool startsWith(RString str);
      virtual vbool startsWith(RString str,vint offset);
      
      virtual RString replace(vchar oldChar,vchar newChar);
      
      virtual void getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin);
      
      static RString valueOf(char i);
      static RString valueOf(vint i);
      static RString valueOf(vbool b);
      static RString valueOf(vchar c);
      static RString valueOf(vlong l);
      static RString valueOf(vfloat f);
      static RString valueOf(vshort s);
      static RString valueOf(vdouble d);
      static RString valueOf(RObject obj);
      static RString valueOf(const char* obj);
      static RString valueOf(const vchar* obj);
      
      static vint indexOf(RArray<vchar> source, vint sourceOffset, vint sourceCount,
                 RArray<vchar> target, vint targetOffset, vint targetCount, vint fromIndex);
      
      static vint lastIndexOf(RArray<vchar> source, vint sourceOffset, vint sourceCount,
                 RArray<vchar> target, vint targetOffset, vint targetCount, vint fromIndex);
      
      virtual RObject clone();
   
   protected:
      virtual void finalize();
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      vint hash;
      
      RArray<vchar> value;
      
      // native string conversion
      vchar* cString;
      void initCString();
      const vchar* toCString();
      
      // native string constructor
      String(const char* val);
      String(const wchar_t* val);
      
      static const RArray<vchar> empty;
      
      // private constructor used internally for speed
      String(RArray<vchar> arr, vbool shared);
      
      void getChars(RArray<vchar> dst, vint dstBegin);
   
   friend class Ref<String>;
   friend class Ref<Object>;
   friend class Ref<Comparable<String>>;
   friend class Ref<io::Streamable<String>>;
};

} /* namespace aro */

#endif /* CORE_STRING_H */
