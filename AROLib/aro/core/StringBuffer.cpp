#include <aro/core/utils/Foreach.hpp>
#include <aro/core/StringBuffer.hpp>

namespace aro {

StringBuffer::StringBuffer()
   :MutableString(16)
{
   
}

StringBuffer::StringBuffer(RString str)
   :MutableString(str->length() + 16)
{
   append(str);
}

StringBuffer::StringBuffer(vint capacity)
   :MutableString(capacity)
{
   
}

vint StringBuffer::length()
{
   vint n = -1;
   
   sync_lock(thisref)
   {
      n = count;
   }
   
   return n;
}

vint StringBuffer::capacity()
{
   vint n = -1;
   
   sync_lock(thisref)
   {
      n = value->length;
   }
   
   return n;
}

void StringBuffer::trimToSize()
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::trimToSize();
   }
}

RString StringBuffer::toString()
{
   sync_lock(thisref)
   {
      if(toStringCache == nullref)
         toStringCache = value->copyOf(0, count);

      return new String(toStringCache, true);
   }
}

vchar StringBuffer::charAt(vint index)
{
   sync_lock(thisref)
   {
      return MutableString::charAt(index);
   }
}

RStringBuffer StringBuffer::reverse()
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::reverse();
   }

   return thisref;
}

void StringBuffer::ensureCapacity(vint min)
{
   sync_lock(thisref)
   {
      MutableString::ensureCapacity(min);
   }
}

void StringBuffer::setLength(vint newLength)
{
   sync_lock(thisref)
   {
      MutableString::setLength(newLength);
   }
}

void StringBuffer::setCharAt(vint index, vchar ch)
{
   sync_lock(thisref)
   {
      MutableString::setCharAt(index, ch);
   }
}

RStringBuffer StringBuffer::append(char c)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(c);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(vint i)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(i);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vbool b)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(b);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vchar c)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(c);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vlong l)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(l);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vfloat f)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(f);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vshort s)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(s);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(vdouble d)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(d);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RObject obj)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(obj);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RString str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(str);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(const char* str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(str);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(const vchar* str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(str);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RStringBuffer sb)
{
   sync_lock(thisref)
   {
      RMutableString rsb = sb;

      toStringCache = nullref;
      MutableString::append(rsb);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RArray<vchar> arr, vint offset, vint count)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::append(arr, offset, count);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, char c)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, c);
   }

   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vint i)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, i);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vbool b)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, b);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vchar c)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, c);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vlong l)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, l);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vfloat f)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, f);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vshort s)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, s);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vdouble d)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, d);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, RObject obj)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, obj);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, RString str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, str);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, const char* str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, str);
   }

   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, const vchar* str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, str);
   }

   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, RArray<vchar> arr)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, arr);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint index, RArray<vchar> arr, vint offset, vint len)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::insert(offset, arr, offset, len);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::removeCharAt(vint index)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::removeCharAt(index);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::remove(vint start, vint end)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::remove(start, end);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::replace(vint start, vint end, RString str)
{
   sync_lock(thisref)
   {
      toStringCache = nullref;
      MutableString::replace(start, end, str);
   }
   
   return thisref;
}

vint StringBuffer::indexOf(RString str)
{
   sync_lock(thisref)
   {
      return MutableString::indexOf(str);
   }
}

vint StringBuffer::indexOf(RString str, vint fromIndex)
{
   sync_lock(thisref)
   {
      return MutableString::indexOf(str, fromIndex);
   }
}

vint StringBuffer::lastIndexOf(RString str)
{
   sync_lock(thisref)
   {
      return MutableString::lastIndexOf(str);
   }
}

vint StringBuffer::lastIndexOf(RString str, vint fromIndex)
{
   sync_lock(thisref)
   {
      return MutableString::lastIndexOf(str, fromIndex);
   }
}

RString StringBuffer::substring(vint start)
{
   sync_lock(thisref)
   {
      return MutableString::substring(start);
   }
}

RString StringBuffer::substring(vint start, vint end)
{
   sync_lock(thisref)
   {
      return MutableString::substring(start, end);
   }
}

void StringBuffer::getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin)
{
   sync_lock(thisref)
   {
      MutableString::getChars(srcBegin, srcEnd, dst, dstBegin);
   }
}

void StringBuffer::readObject(io::RObjectInputStream is)
{
   sync_lock(thisref)
   {
      count = is->readInt();
      value = type_cast<Array<vchar>>(is->readObject());
   }
}

void StringBuffer::writeObject(io::RObjectOutputStream os)
{
   sync_lock(thisref)
   {
      os->writeInt(count);
      os->writeObject(value);
   }
}

} /* namespace aro */
