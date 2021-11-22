#include <aro/core/utils/Foreach.hpp>
#include <aro/core/StringBuilder.hpp>

namespace aro {

StringBuilder::StringBuilder()
   :MutableString(16)
{
   
}

StringBuilder::StringBuilder(RString str)
   :MutableString(str->length() + 16)
{
   append(str);
}

StringBuilder::StringBuilder(vint capacity)
   :MutableString(capacity)
{
   
}

RString StringBuilder::toString()
{
   return new String(value, 0, count);
}

RStringBuilder StringBuilder::reverse()
{
   MutableString::reverse();
   
   return thisref;
}

RStringBuilder StringBuilder::append(char c)
{
   return append(String::valueOf(c));
}

RStringBuilder StringBuilder::append(vint i)
{
   return append(String::valueOf(i));
}

RStringBuilder StringBuilder::append(vbool b)
{
   MutableString::append(b);
   
	return thisref;
}

RStringBuilder StringBuilder::append(vchar c)
{
   MutableString::append(c);
   
   return thisref;
}

RStringBuilder StringBuilder::append(vlong l)
{
   return append(String::valueOf(l));
}

RStringBuilder StringBuilder::append(vfloat f)
{
   return append(String::valueOf(f));
}

RStringBuilder StringBuilder::append(vshort s)
{
   return append(String::valueOf(s));
}

RStringBuilder StringBuilder::append(vdouble d)
{
   return append(String::valueOf(d));
}

RStringBuilder StringBuilder::append(RObject obj)
{
   return append(String::valueOf(obj));
}

RStringBuilder StringBuilder::append(RString str)
{
   MutableString::append(str);
   
   return thisref;
}

RStringBuilder StringBuilder::append(const char* str)
{
   return append(String::valueOf(str));
}

RStringBuilder StringBuilder::append(const vchar* str)
{
   return append(String::valueOf(str));
}

RStringBuilder StringBuilder::append(RArray<vchar> arr)
{
   MutableString::append(arr);
   
   return thisref;
}

RStringBuilder StringBuilder::append(RStringBuilder sb)
{
   MutableString::append(RMutableString(sb));
   
   return thisref;
}

RStringBuilder StringBuilder::append(RArray<vchar> arr, vint offset, vint len)
{
   MutableString::append(arr, offset, len);
   
   return thisref;
}

RStringBuilder StringBuilder::insert(vint index, char c)
{
   return insert(index, String::valueOf(c));
}

RStringBuilder StringBuilder::insert(vint index, vint i)
{
   return insert(index, String::valueOf(i));
}

RStringBuilder StringBuilder::insert(vint index, vbool b)
{
   return insert(index, String::valueOf(b));
}

RStringBuilder StringBuilder::insert(vint index, vchar c)
{
   return insert(index, String::valueOf(c));
}

RStringBuilder StringBuilder::insert(vint index, vlong l)
{
   return insert(index, String::valueOf(l));
}

RStringBuilder StringBuilder::insert(vint index, vfloat f)
{
   return insert(index, String::valueOf(f));
}

RStringBuilder StringBuilder::insert(vint index, vshort s)
{
   return insert(index, String::valueOf(s));
}

RStringBuilder StringBuilder::insert(vint index, vdouble d)
{
   return insert(index, String::valueOf(d));
}

RStringBuilder StringBuilder::insert(vint index, RObject obj)
{
   return insert(index, String::valueOf(obj));
}

RStringBuilder StringBuilder::insert(vint index, RString str)
{
   MutableString::insert(index, str);
   
   return thisref;
}

RStringBuilder StringBuilder::insert(vint index, const char* str)
{
   return insert(index, String::valueOf(str));
}

RStringBuilder StringBuilder::insert(vint index, const vchar* str)
{
   return insert(index, String::valueOf(str));
}

RStringBuilder StringBuilder::insert(vint index, RArray<vchar> arr)
{
   MutableString::insert(index, arr);
   
   return thisref;
}

RStringBuilder StringBuilder::insert(vint index, RArray<vchar> arr, vint offset, vint len)
{
   MutableString::insert(index, arr, offset, len);
   
   return thisref;
}

RStringBuilder StringBuilder::removeCharAt(vint index)
{
   MutableString::removeCharAt(index);
   
   return thisref;
}

RStringBuilder StringBuilder::remove(vint start, vint end)
{
   MutableString::remove(start, end);
   
   return thisref;
}

RStringBuilder StringBuilder::replace(vint start, vint end, RString str)
{
   MutableString::replace(start, end, str);
   
   return thisref;
}

vint StringBuilder::indexOf(RString str)
{
   return MutableString::indexOf(str);
}

vint StringBuilder::indexOf(RString str, vint offset)
{
   return MutableString::indexOf(str, offset);
}

vint StringBuilder::lastIndexOf(RString str)
{
   return MutableString::lastIndexOf(str);
}

vint StringBuilder::lastIndexOf(RString str, vint offset)
{
   return MutableString::lastIndexOf(str, offset);
}

void StringBuilder::readObject(io::RObjectInputStream is)
{
   count = is->readInt();
   value = type_cast<Array<vchar>>(is->readObject());
}

void StringBuilder::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(count);
   os->writeObject(value);
}

} /* namespace aro */
