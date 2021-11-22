#ifndef CORE_MUTABLESTRING_H
#define CORE_MUTABLESTRING_H

#include <aro/core/String.hpp>

namespace aro {

class MutableString;
typedef Ref<MutableString> RMutableString;

class MutableString : public Object
{
   public:
      vint length();
      vint capacity();

      void trimToSize();
      RString toString() = 0;
      vchar charAt(vint index);
      RMutableString reverse();
      void ensureCapacity(vint min);
      void setLength(vint newLength);
      void setCharAt(vint index, vchar ch);

      RMutableString append(char c);
      RMutableString append(vint i);
      RMutableString append(vbool b);
      RMutableString append(vchar c);
      RMutableString append(vlong l);
      RMutableString append(vfloat f);
      RMutableString append(vshort s);
      RMutableString append(vdouble d);
      RMutableString append(RObject obj);
      RMutableString append(RString str);
      RMutableString append(const char* str);
      RMutableString append(const vchar* str);
      RMutableString append(RArray<vchar> arr);
      RMutableString append(RMutableString sb);
      RMutableString append(RArray<vchar> arr, vint offset, vint len);

      RMutableString insert(vint index, char c);
      RMutableString insert(vint index, vint i);
      RMutableString insert(vint index, vbool b);
      RMutableString insert(vint index, vchar c);
      RMutableString insert(vint index, vlong l);
      RMutableString insert(vint index, vfloat f);
      RMutableString insert(vint index, vshort s);
      RMutableString insert(vint index, vdouble d);
      RMutableString insert(vint index, RObject obj);
      RMutableString insert(vint index, RString str);
      RMutableString insert(vint index, const char* str);
      RMutableString insert(vint index, const vchar* str);
      RMutableString insert(vint index, RArray<vchar> arr);
      RMutableString insert(vint index, RArray<vchar> arr, vint offset, vint len);

      RMutableString removeCharAt(vint index);
      RMutableString remove(vint start, vint end);
      RMutableString replace(vint start, vint end, RString str);

      vint indexOf(RString str);
      vint indexOf(RString str, vint fromIndex);

      vint lastIndexOf(RString str);
      vint lastIndexOf(RString str, vint fromIndex);

      RString substring(vint start);
      RString substring(vint start, vint end);

      void getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin);
   
   protected:
      MutableString(vint capacity);
   
   private:
      vint count;
      RArray<vchar> value;

      void expandCapacity(vint min);

   friend class StringBuilder;
   friend class StringBuffer;
};

} /* namespace aro */

#endif /* CORE_MUTABLESTRING_H */
