#include <aro/core/utils/Foreach.h>
#include <aro/core/StringBuilder.h>

namespace aro {

StringBuilder::StringBuilder()
{
   count = 0;
   value = new Array<vchar>(16);
}

StringBuilder::StringBuilder(RString str)
{
   count = 0;
   value = new Array<vchar>(str->length()+16);
   
   append(str);
}

StringBuilder::StringBuilder(vint capacity)
{
   count = 0;
   value = new Array<vchar>(capacity);
}

vint StringBuilder::length()
{
   return count;
}

vint StringBuilder::capacity()
{
   return value->length;
}

void StringBuilder::trimToSize()
{
   if(count < value->length)
      value = value->copyOf(count);
}

RString StringBuilder::toString()
{
   return new String(value, 0, count);
}

vchar StringBuilder::charAt(vint index)
{
   if(index < 0 || index >= count)
      ex_throw new IndexException(index);
   
   return value[index];
}

RStringBuilder StringBuilder::reverse()
{
   vint n = count-1;
   
   for(vint j=(n-1)>>1; j>=0; --j)
   {
      vchar temp = value[j];
      value[j] = value[n-j];
      value[n-j] = temp;
   }
   
   return thisref;
}

void StringBuilder::ensureCapacity(vint min)
{
   if(min > value->length)
      expandCapacity(min);
}

void StringBuilder::expandCapacity(vint min)
{
   vint newCapacity = (value->length+1)*2;
   if(min > newCapacity) newCapacity = min;
   value = value->copyOf(newCapacity);
}

void StringBuilder::setLength(vint newLength)
{
   if(newLength < 0)
      ex_throw new IndexException(newLength);
   
   if(newLength > value->length)
      expandCapacity(newLength);
   
	if(count < newLength)
	{
	   for(; count < newLength; count++)
		   value[count] = '\0';
	}
	else
	{
      count = newLength;
   }
}

void StringBuilder::setCharAt(vint index, vchar ch)
{
   if(index < 0 || index >= count)
      ex_throw new IndexException(index);
   
   value[index] = ch;
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
   if(b)
   {
      vint newCount = count + 4;
      if(newCount > value->length)
         expandCapacity(newCount);
      value[count++] = 't';
      value[count++] = 'r';
      value[count++] = 'u';
      value[count++] = 'e';
   }
   else
   {
      vint newCount = count + 5;
      if(newCount > value->length)
         expandCapacity(newCount);
      value[count++] = 'f';
      value[count++] = 'a';
      value[count++] = 'l';
      value[count++] = 's';
      value[count++] = 'e';
   }
   
	return thisref;
}

RStringBuilder StringBuilder::append(vchar c)
{
   vint newCount = count+1;
   if(newCount > value->length)
      expandCapacity(newCount);
   value[count++] = c;
   
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
   if(str == nullref) str = "null";
   
   vint len = str->length();
   if(len == 0) return thisref;
   
   vint newCount = count + len;
   if(newCount > value->length)
      expandCapacity(newCount);
   str->getChars(0, len, value, count);
   count = newCount;
   
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
   vint newCount = count + arr->length;
   if(newCount > value->length)
      expandCapacity(newCount);
   
   value->copy(count, arr, 0, arr->length);
   count = newCount;
   
   return thisref;
}

RStringBuilder StringBuilder::append(RStringBuilder sb)
{
   if(sb == nullref)
      return append("nullref");
   
   vint len = sb->length();
   vint newCount = count+len;
   if(newCount > value->length)
      expandCapacity(newCount);
   sb->getChars(0, len, value, count);
   count = newCount;
   
   return thisref;
}

RStringBuilder StringBuilder::append(RArray<vchar> arr, vint offset, vint len)
{
   vint newCount = count+len;
   if(newCount > value->length)
      expandCapacity(newCount);
   
   value->copy(count, arr, offset, len);
   count = newCount;
   
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
   if(index < 0 || index >= count)
      ex_throw new IndexException(index);
   
   if(str == nullref)
      str = "null";
   vint len = str->length();
   vint newCount = count + len;
   if(newCount > value->length)
      expandCapacity(newCount);
   
   value->copy(index + len, value, index, count - index);
   str->getChars(0, len, value, index);
   count = newCount;
   
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
   if(index < 0 || index >= count)
      ex_throw new IndexException(index);
   
   vint len = arr->length;
   vint newCount = count + len;
   if(newCount > value->length)
      expandCapacity(newCount);
   
   value->copy(index + len, value, index, count - index);
   value->copy(index, arr, 0, len);
   count = newCount;
   
   return thisref;
}

RStringBuilder StringBuilder::insert(vint index, RArray<vchar> arr, vint offset, vint len)
{
   if(index < 0 || index >= count)
      ex_throw new IndexException(index);
   
   if(offset < 0 || len < 0 || offset > arr->length - len)
      ex_throw new IndexException("offset: " + String::valueOf(offset) +
               ", len: " + String::valueOf(len) + ", arr->length: " +
               String::valueOf(arr->length));
   
   vint newCount = count + len;
   if(newCount > value->length)
      expandCapacity(newCount);
   
   value->copy(index + len, value, index, count - index);
   value->copy(index, arr, offset, len);
   count = newCount;
   
   return thisref;
}

RStringBuilder StringBuilder::removeCharAt(vint index)
{
   if(index < 0 || index >= count)
      ex_throw new IndexException(index);
   
   value->copy(index, value, index+1, count-index-1);
   
   count--;
   
   return thisref;
}

RStringBuilder StringBuilder::remove(vint start, vint end)
{
   if(start < 0)
      ex_throw new IndexException(start);
   
   if(end > count)
      end = count;
   
   if(start > end)
      ex_throw new IndexException(end-start);
   
   vint len = end - start;
   
   if(len > 0)
   {
      value->copy(start, value, start+len, count-end);
      count -= len;
   }
   
   return thisref;
}

RStringBuilder StringBuilder::replace(vint start, vint end, RString str)
{
   if(start < 0)
	   ex_throw new IndexException(start);
	if(start > count)
	   ex_throw new IndexException("start > length()");
	if(start > end)
	   ex_throw new IndexException("start > end");
	
	if(end > count)
	   end = count;
	
	vint len = str->length();
	vint newCount = count + len - (end - start);
	if(newCount > value->length)
	   expandCapacity(newCount);
   
   value->copy(start + len, value, end, count - end);
   str->getChars(0, len, value, start);
   count = newCount;
   
   return thisref;
}

vint StringBuilder::indexOf(RString str)
{
   return indexOf(str, 0);
}

vint StringBuilder::indexOf(RString str, vint offset)
{
   return String::indexOf(value, 0, count,
                  str->toCharArray(), 0, str->length(), offset);
}

vint StringBuilder::lastIndexOf(RString str)
{
   return lastIndexOf(str, 0);
}

vint StringBuilder::lastIndexOf(RString str, vint offset)
{
   return String::lastIndexOf(value, 0, count,
                  str->toCharArray(), 0, str->length(), offset);
}

RString StringBuilder::substring(vint start)
{
   return substring(start, count);
}

RString StringBuilder::substring(vint start, vint end)
{
   if(start < 0)
      ex_throw new IndexException(start);
   if(end > count)
      ex_throw new IndexException(end);
   if(start > end)
      ex_throw new IndexException(end - start);
   
   return new String(value, start, end - start);
}

void StringBuilder::getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin)
{
   if(srcBegin < 0)
      ex_throw new IndexException(srcBegin);
   
   if(srcEnd < 0 || srcEnd > count)
      ex_throw new IndexException(srcEnd);
   
   if(srcBegin > srcEnd)
      ex_throw new IndexException("srcBegin > srcEnd");
   
   dst->copy(dstBegin, value, srcBegin, srcEnd - srcBegin);
}

} /* namespace aro */
