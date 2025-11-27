#include <sstream>
#include <iostream>
#include <aro/core/utils/Foreach.hpp>

// for use with stringstream
using namespace std;

namespace aro {

const RArray<vchar> String::empty = new Array<vchar>(0);

const RString String::EMPTY_STRING = new String();

String::String()
	:String(empty, true)
{
   
}

String::String(RString str)
{
   initCString();
   hash = str->hash;
   value = str->value;
}

String::String(RArray<vchar> arr)
   :String(arr, 0, arr->length)
{
	
}

String::String(RArray<vchar> arr, vint offset, vint count)
{
	if (count < 0)
		ex_throw new IndexException("String Index out of Bounds: ", count);

	if (offset < 0)
		ex_throw new IndexException("String Index out of Bounds: ", offset);
   
   if(count == 0 && offset <= arr->length)
      value = empty;
   else
   {
      if(offset > arr->length - count)
         ex_throw new IndexException("String Index out of Bounds: ", offset + count);

      value = arr->copyOf(offset, count);
   }
   
   initCString();
   hash = 0;
}

RArray<vchar> String::toCharArray()
{
	return new Array<vchar>(value);
}

vchar String::charAt(vint index)
{
	if (index < 0 || index >= value->length)
		ex_throw new IndexException("String index out of bounds: ", index);

	return value[index];
}

vint String::length()
{
	return value->length;
}

vint String::hashCode()
{
	vint h = hash;
	vint len = value->length;

	if (h == 0 && len > 0)
	{
		RArray<vchar> val = value;

		for (vint i = 0; i < len; i++)
			h = 31 * h + val[i];

		hash = h;
	}

	return h;
}

vbool String::isEmpty()
{
   return value->length == 0;
}

RString String::toLowerCase()
{
	RArray<vchar> arr = new Array<vchar>(value->length);

	for (vint n = 0; n < arr->length; n++)
		arr[n] = tolower(value[n]);
   
	return new String(arr, true);
}

RString String::toUpperCase()
{
	RArray<vchar> arr = new Array<vchar>(value->length);

	for (vint n = 0; n < arr->length; n++)
		arr[n] = toupper(value[n]);
   
	return new String(arr, true);
}

RString String::toString()
{
	return thisref;
}

RString String::concat(RString str)
{
   vint strLen = str->length();
	if (strLen == 0)
		return thisref;

   vint len = value->length;
   
   RArray<vchar> arr = value->copyOf(len + strLen);

   str->getChars(arr, len);
   
	return new String(arr, true);
}

vbool String::equals(RObject obj)
{
	if (obj == thisref)
		return true;

	if (type_of<String>(obj))
	{
		RString str = type_cast<String>(obj);

		vint n = value->length;

		if (n == str->value->length)
		{
			RArray<vchar> v1 = value;
			RArray<vchar> v2 = str->value;

			vint i = 0;
			while (n-- != 0)
			{
				if (v1[i] != v2[i])
					return false;
            
            i++;
			}

			return true;
		}
	}

	return false;
}

vint String::compareTo(RString str)
{
	vint len1 = value->length;
	vint len2 = str->value->length;
	vint lim = Math::minimum(len1, len2);
	RArray<vchar> v1 = value, v2 = str->value;
   
	vint k = 0;
	while (k < lim)
	{
		vchar c1 = v1[k];
		vchar c2 = v2[k];
      
		if (c1 != c2)
			return c1 - c2;
      
		k++;
	}
   
	return len1 - len2;
}

vbool String::startsWith(RString prefix)
{
	return startsWith(prefix, 0);
}

vbool String::startsWith(RString prefix, vint toffset)
{
	RArray<vchar> ta = value;
	vint to = toffset;
	RArray<vchar> pa = prefix->value;
	vint po = 0;
	vint pc = prefix->value->length;

	if (toffset < 0 || toffset > value->length - pc)
		return false;

	while (--pc >= 0)
	{
		if (ta[to++] != pa[po++])
			return false;
	}

	return true;
}

vbool String::endsWith(RString suffix)
{
	return startsWith(suffix, value->length - suffix->value->length);
}

vint String::indexOf(vchar ch)
{
	return indexOf(ch, 0);
}

vint String::indexOf(RString str)
{
	return indexOf(str, 0);
}

vint String::indexOf(vchar ch, vint from)
{
	if (from < 0)
      from = 0;

	vint max = value->length;

	for (vint i = from; i < max; i++)
	{
		if (value[i] == ch)
			return i;
	}

	return -1;
}

vint String::indexOf(RString str, vint offset)
{
	return indexOf(value, offset, value->length, str->value,
		0, str->value->length, offset);
}

vint String::lastIndexOf(vchar ch)
{
	return lastIndexOf(ch, value->length - 1);
}

vint String::lastIndexOf(RString str)
{
	return lastIndexOf(str, value->length);
}

vint String::lastIndexOf(vchar ch, vint from)
{
	if (from >= value->length)
		from = value->length - 1;

	vint min = from;

	for (vint i = min; i >= 0; i--)
	{
		if (value[i] == ch)
			return i;
	}

	return -1;
}

vint String::lastIndexOf(RString str, vint offset)
{
	return lastIndexOf(value, 0, value->length,
		str->value, 0, str->value->length, offset);
}

RString String::substring(vint from)
{
	return substring(from, value->length);
}

RString String::substring(vint from, vint end)
{
	if (from < 0)
		ex_throw new IndexException("String index out of bounds: ", from);

	if (end > value->length)
		ex_throw new IndexException("String index out of bounds: ", end);

	if (from > end)
		ex_throw new IndexException("Invalid substring size: ", end - from);

	if (from == 0 && end == value->length)
		return thisref;

	return new String(value, from, end - from);
}

RString String::replace(vchar oldChar, vchar newChar)
{
	if (oldChar != newChar)
	{
		RArray<vchar> val = value;
		vint len = value->length;
		vint i = -1;

		while (++i < len)
		{
			if (val[i] == oldChar)
				break;
		}

		if (i < len)
		{
			RArray<vchar> buf = new Array<vchar>(len);
			for (vint j = 0; j < i; j++)
				buf[j] = val[j];

			while (i < len)
			{
				vchar c = val[i];
				buf[i] = (c == oldChar) ? newChar : c;
				i++;
			}

			return new String(buf, true);
		}
	}

	return thisref;
}

RString String::trim()
{
	vint st = 0;
	vint len = value->length;
	RArray<vchar> val = value;

	while (st < len && value[st] <= ' ')
		st++;

	while (st < len && value[len - 1] <= ' ')
		len--;

	if (st > 0 || len < value->length)
		return substring(st, len);

	return thisref;
}

vbool String::equalsIgnoreCase(RString str)
{
	return toLowerCase()->equals(str->toLowerCase());
}

vint String::compareToIgnoreCase(RString str)
{
	return toLowerCase()->compareTo(str->toLowerCase());
}

RObject String::clone()
{
    RString str = type_cast<String>(Object::clone());

    str->initCString();

    return str;
}

void String::getChars(RArray<vchar> dst, vint dstBegin)
{
   dst->copy(dstBegin, value, 0, value->length);
}

void String::getChars(vint srcBegin, vint srcEnd, RArray<vchar> dst, vint dstBegin)
{
	if (srcBegin < 0)
		ex_throw new IndexException("String Index Out of Bounds: ", srcBegin);

	if (srcEnd > value->length)
		ex_throw new IndexException("String Index Out of Bounds: ", srcEnd);

	if (srcBegin > srcEnd)
		ex_throw new IndexException("String Index Out of Bounds: ", srcEnd - srcBegin);

	dst->copy(dstBegin, value, srcBegin, srcEnd - srcBegin);
}

void String::writeObject(io::RObjectOutputStream os)
{
	os->writeInt(hash);
	os->writeObject(value);
}

void String::readObject(io::RObjectInputStream is)
{
	hash = is->readInt();
	value = type_cast<Array<vchar>>(is->readObject());
}

RString String::valueOf(vint val)
{
	wstringstream ss;

	ss << val;

	return ss.str().c_str();
}

RString String::valueOf(char val)
{
   wstringstream ss;

   ss << val;

   return ss.str().c_str();
}

RString String::valueOf(vbool val)
{
	return val ? L"true" : L"false";
}

RString String::valueOf(vchar val)
{
	wstringstream ss;

	ss << val;

	return ss.str().c_str();
}

RString String::valueOf(vlong val)
{
	wstringstream ss;

	ss << val;

	return ss.str().c_str();
}

RString String::valueOf(vfloat val)
{
	wstringstream ss;

	ss << val;

	return ss.str().c_str();
}

RString String::valueOf(vshort val)
{
	wstringstream ss;

	ss << val;

	return ss.str().c_str();
}

RString String::valueOf(vdouble val)
{
	wstringstream ss;

	ss << val;

	return ss.str().c_str();
}

RString String::valueOf(RObject obj)
{
	return obj == nullref ? L"null" : obj->toString();
}

RString String::valueOf(const char* str)
{
   return new String(str);
}

RString String::valueOf(const vchar* str)
{
   return new String(str);
}

vint String::indexOf(RArray<vchar> source, vint sourceOffset, vint sourceCount,
	RArray<vchar> target, vint targetOffset, vint targetCount, vint fromIndex)
{
	if (fromIndex >= sourceCount)
		return (targetCount == 0 ? sourceCount : -1);

	if (fromIndex < 0)
		fromIndex = 0;

	if (targetCount == 0)
		return fromIndex;

	vchar first = target[targetOffset];
	vint max = sourceOffset + (sourceCount - targetCount);

	for (vint i = sourceOffset + fromIndex; i <= max; i++)
	{
		/* Look for first character */
		if (source[i] != first)
		while (++i <= max && source[i] != first);

		/* Found first character, now look at the rest of v2 */
		if (i <= max)
		{
			vint j = i + 1;
			vint end = j + targetCount - 1;
			for (vint k = targetOffset + 1; j < end && source[j] == target[k]; j++, k++);

			if (j == end)
				/* Found whole string. */
				return i - sourceOffset;
		}
	}

	return -1;
}

vint String::lastIndexOf(RArray<vchar> source, vint sourceOffset, vint sourceCount,
	RArray<vchar> target, vint targetOffset, vint targetCount, vint fromIndex)
{
	/* Check arguments; return immediately where possible.
		* For consistency, don't check for nullref str. */
	vint rightIndex = sourceCount - targetCount;
	if (fromIndex < 0)
		return -1;

	if (fromIndex > rightIndex)
		fromIndex = rightIndex;

	/* Empty string always matches. */
	if (targetCount == 0)
		return fromIndex;

	vint strLastIndex = targetOffset + targetCount - 1;
	vchar strLastChar = target[strLastIndex];
	vint min = sourceOffset + targetCount - 1;
	vint i = min + fromIndex;

	while (true)
	{
		while (true)
		{
			while (i >= min && source[i] != strLastChar)
				i--;

			if (i < min)
				return -1;

			vint j = i - 1;
			vint start = j - (targetCount - 1);
			vint k = strLastIndex - 1;

			vbool restart = false;

			while (j > start)
			{
				if (source[j--] != target[k--])
				{
					i--;
					restart = true;
					break;
				}
			}

			if (restart) break;

			return start - sourceOffset + 1;
		}
	}
}

void String::finalize()
{
   if(cString != nullptr)
      delete[] cString;
   
   Object::finalize();
}

String::String(const wchar_t* val)
{
   if(val == nullptr)
      ex_throw new ArgumentException(L"Null string literal");
   
   vint len = (vint)wcslen(val);

   if(len == 0)
      value = empty;
   else
   {
      value = new Array<vchar>(len);
      
      for(vint n = 0; n < len; n++)
         value[n] = val[n];
   }
   
   initCString();
   hash = 0;
}

String::String(const char* val)
{
   if (val == nullptr)
      ex_throw new ArgumentException("Null string literal");
   
   vint len = (vint)strlen(val);
   
   if(len == 0)
      value = empty;
   else
   {
      value = new Array<vchar>(len);
      
      for(vint n = 0; n < len; n++)
         value[n] = val[n];
   }
   
   initCString();
   hash = 0;
}

void String::initCString()
{
   cString = nullptr;
}

const vchar* String::toCString()
{
   if(cString == nullptr)
   {
      cString = new vchar[value->length+1];
      
      for(vint n = 0; n < value->length; n++)
         cString[n] = value[n];
      
      cString[value->length] = L'\0';
   }
   
   return cString;
}

// private constructor which shares array for speed
String::String(RArray<vchar> arr, vbool shared)
{
   initCString();
   value = arr;
   hash = 0;
}

} /* namespace aro */
