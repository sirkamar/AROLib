#include <aro/core/utils/Foreach.h>
#include <aro/core/StringBuffer.h>

namespace aro {

StringBuffer::StringBuffer()
{
   
}

StringBuffer::StringBuffer(RString str)
   :StringBuilder(str)
{
   
}

StringBuffer::StringBuffer(vint capacity)
   :StringBuilder(capacity)
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
      StringBuilder::trimToSize();
   }
}

RString StringBuffer::toString()
{
   sync_lock(thisref)
   {
      return StringBuilder::toString();
   }
}

vchar StringBuffer::charAt(vint index)
{
   sync_lock(thisref)
   {
      return StringBuilder::charAt(index);
   }
}

RStringBuffer StringBuffer::reverse()
{
   sync_lock(thisref)
   {
      StringBuilder::reverse();
   }

   return thisref;
}

void StringBuffer::ensureCapacity(vint min)
{
   sync_lock(thisref)
   {
      expandCapacity(min);
   }
}

void StringBuffer::setLength(vint newLength)
{
   sync_lock(thisref)
   {
      StringBuilder::setLength(newLength);
   }
}

void StringBuffer::setCharAt(vint index, vchar ch)
{
   sync_lock(thisref)
   {
      StringBuilder::setCharAt(index, ch);
   }
}

RStringBuffer StringBuffer::append(char c)
{
   sync_lock(thisref)
   {
      StringBuilder::append(c);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(vint i)
{
   sync_lock(thisref)
   {
      StringBuilder::append(i);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vbool b)
{
   sync_lock(thisref)
   {
      StringBuilder::append(b);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vchar c)
{
   sync_lock(thisref)
   {
      StringBuilder::append(c);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vlong l)
{
   sync_lock(thisref)
   {
      StringBuilder::append(l);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vfloat f)
{
   sync_lock(thisref)
   {
      StringBuilder::append(f);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::append(vshort s)
{
   sync_lock(thisref)
   {
      StringBuilder::append(s);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(vdouble d)
{
   sync_lock(thisref)
   {
      StringBuilder::append(d);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RObject obj)
{
   sync_lock(thisref)
   {
      StringBuilder::append(obj);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RString str)
{
   sync_lock(thisref)
   {
      StringBuilder::append(str);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(const char* str)
{
   sync_lock(thisref)
   {
      StringBuilder::append(str);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(const vchar* str)
{
   sync_lock(thisref)
   {
      StringBuilder::append(str);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RStringBuffer sb)
{
   sync_lock(thisref)
   {
      RStringBuilder rsb = sb;

      StringBuilder::append(rsb);
   }

   return thisref;
}

RStringBuffer StringBuffer::append(RArray<vchar> arr, vint offset, vint count)
{
   sync_lock(thisref)
   {
      StringBuilder::append(arr, offset, count);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, char c)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, c);
   }

   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vint i)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, i);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vbool b)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, b);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vchar c)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, c);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vlong l)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, l);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vfloat f)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, f);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vshort s)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, s);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, vdouble d)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, d);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, RObject obj)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, obj);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, RString str)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, str);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, const char* str)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, str);
   }

   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, const vchar* str)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, str);
   }

   return thisref;
}

RStringBuffer StringBuffer::insert(vint offset, RArray<vchar> arr)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, arr);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::insert(vint index, RArray<vchar> arr, vint offset, vint len)
{
   sync_lock(thisref)
   {
      StringBuilder::insert(offset, arr, offset, len);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::removeCharAt(vint index)
{
   sync_lock(thisref)
   {
      StringBuilder::removeCharAt(index);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::remove(vint start, vint end)
{
   sync_lock(thisref)
   {
      StringBuilder::remove(start, end);
   }
   
   return thisref;
}

RStringBuffer StringBuffer::replace(vint start, vint end, RString str)
{
   sync_lock(thisref)
   {
      StringBuilder::replace(start, end, str);
   }
   
   return thisref;
}

vint StringBuffer::indexOf(RString str)
{
   sync_lock(thisref)
   {
      return StringBuilder::indexOf(str);
   }
}

vint StringBuffer::indexOf(RString str, vint fromIndex)
{
   sync_lock(thisref)
   {
      return StringBuilder::indexOf(str, fromIndex);
   }
}

vint StringBuffer::lastIndexOf(RString str)
{
   sync_lock(thisref)
   {
      return StringBuilder::lastIndexOf(str);
   }
}

vint StringBuffer::lastIndexOf(RString str, vint fromIndex)
{
   sync_lock(thisref)
   {
      return StringBuilder::lastIndexOf(str, fromIndex);
   }
}

RString StringBuffer::substring(vint start)
{
   sync_lock(thisref)
   {
      return StringBuilder::substring(start);
   }
}

RString StringBuffer::substring(vint start, vint end)
{
   sync_lock(thisref)
   {
      return StringBuilder::substring(start, end);
   }
}

void StringBuffer::getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin)
{
   sync_lock(thisref)
   {
      StringBuilder::getChars(srcBegin, srcEnd, dst, dstBegin);
   }
}

} /* namespace aro */
