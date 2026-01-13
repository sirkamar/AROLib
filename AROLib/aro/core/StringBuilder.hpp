#ifndef CORE_STRINGBUILDER_H
#define CORE_STRINGBUILDER_H

#include <aro/core/MutableString.hpp>

namespace aro {

class StringBuilder;
typedef Ref<StringBuilder> RStringBuilder;

class StringBuilder final extends public MutableString implements public io::Streamable<StringBuilder>
{
   public:
      StringBuilder();
      StringBuilder(RString str);
      StringBuilder(vint capacity);
      
      RString toString();

      RStringBuilder reverse();
      
      RStringBuilder append(char i);
      RStringBuilder append(vint i);
      RStringBuilder append(vbool b);
      RStringBuilder append(vchar c);
      RStringBuilder append(vlong l);
      RStringBuilder append(vfloat f);
      RStringBuilder append(vshort s);
      RStringBuilder append(vdouble d);
      RStringBuilder append(RObject obj);
      RStringBuilder append(RString str);
      RStringBuilder append(const char* str);
      RStringBuilder append(const vchar* str);
      RStringBuilder append(RArray<vchar> arr);
      RStringBuilder append(RStringBuilder sb);
      RStringBuilder append(RArray<vchar> arr, vint offset, vint len);
      
      RStringBuilder insert(vint index, char c);
      RStringBuilder insert(vint index, vint i);
      RStringBuilder insert(vint index, vbool b);
      RStringBuilder insert(vint index, vchar c);
      RStringBuilder insert(vint index, vlong l);
      RStringBuilder insert(vint index, vfloat f);
      RStringBuilder insert(vint index, vshort s);
      RStringBuilder insert(vint index, vdouble d);
      RStringBuilder insert(vint index, RObject obj);
      RStringBuilder insert(vint index, RString str);
      RStringBuilder insert(vint index, const char* str);
      RStringBuilder insert(vint index, const vchar* str);
      RStringBuilder insert(vint index, RArray<vchar> arr);
      RStringBuilder insert(vint index, RArray<vchar> arr, vint offset, vint len);
      
      RStringBuilder removeCharAt(vint index);
      RStringBuilder remove(vint start, vint end);
      RStringBuilder replace(vint start, vint end, RString str);
      
      vint indexOf(RString str);
      vint indexOf(RString str, vint fromIndex);
      
      vint lastIndexOf(RString str);
      vint lastIndexOf(RString str, vint fromIndex);
   
   protected:
      void readObject(io::RObjectInputStream is);
      void writeObject(io::RObjectOutputStream os);
};

} /* namespace aro */

#endif /* CORE_STRINGBUILDER_H */
