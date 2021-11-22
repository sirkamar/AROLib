#ifndef CORE_STRINGBUFFER_H
#define CORE_STRINGBUFFER_H

#include <aro/core/MutableString.hpp>

namespace aro {

class StringBuffer;
typedef Ref<StringBuffer> RStringBuffer;

class StringBuffer : public MutableString, public io::Streamable<StringBuffer>
{
   public:
      StringBuffer();
      StringBuffer(RString str);
      StringBuffer(vint capacity);
      
      vint length();
      vint capacity();
      
      void trimToSize();
      RString toString();
      vchar charAt(vint index);
      RStringBuffer reverse();
      void ensureCapacity(vint min);
      void setLength(vint newLength);
      void setCharAt(vint index, vchar ch);
      
      RStringBuffer append(char c);
      RStringBuffer append(vint i);
      RStringBuffer append(vbool b);
      RStringBuffer append(vchar c);
      RStringBuffer append(vlong l);
      RStringBuffer append(vfloat f);
      RStringBuffer append(vshort s);
      RStringBuffer append(vdouble d);
      RStringBuffer append(RObject obj);
      RStringBuffer append(RString str);
      RStringBuffer append(const char* str);
      RStringBuffer append(const vchar* str);
      RStringBuffer append(RArray<vchar> arr);
      RStringBuffer append(RStringBuffer sb);
      RStringBuffer append(RArray<vchar> arr, vint offset, vint count);
      
      RStringBuffer insert(vint index, char c);
      RStringBuffer insert(vint index, vint i);
      RStringBuffer insert(vint index, vbool b);
      RStringBuffer insert(vint index, vchar c);
      RStringBuffer insert(vint index, vlong l);
      RStringBuffer insert(vint index, vfloat f);
      RStringBuffer insert(vint index, vshort s);
      RStringBuffer insert(vint index, vdouble d);
      RStringBuffer insert(vint index, RObject obj);
      RStringBuffer insert(vint index, RString str);
      RStringBuffer insert(vint index, const char* str);
      RStringBuffer insert(vint index, const vchar* str);
      RStringBuffer insert(vint index, RArray<vchar> arr);
      RStringBuffer insert(vint index, RArray<vchar> arr, vint offset, vint len);
      
      RStringBuffer removeCharAt(vint index);
      RStringBuffer remove(vint start, vint end);
      RStringBuffer replace(vint start, vint end, RString str);
      
      vint indexOf(RString str);
      vint indexOf(RString str, vint fromIndex);
      
      vint lastIndexOf(RString str);
      vint lastIndexOf(RString str, vint fromIndex);
      
      RString substring(vint start);
      RString substring(vint start, vint end);
      
      void getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin);
   
   protected:
      void readObject(io::RObjectInputStream is);
      void writeObject(io::RObjectOutputStream os);
   
   private:
      RArray<vchar> toStringCache;
};

} /* namespace aro */

#endif /* CORE_STRINGBUFFER_H */
