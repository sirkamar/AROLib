#include <aro/util/StringTokenizer.h>

namespace aro {

namespace util {

StringTokenizer::StringTokenizer(RString str)
{
   cur = 0;
   next = -1;
   string = str;
   changed = false;
   delim = " \t\n\r\f";
   maxPos = str->length();
}

StringTokenizer::StringTokenizer(RString str, RString d)
{
   cur = 0;
   next = -1;
   delim = d;
   string = str;
   changed = false;
   maxPos = str->length();
}

RString StringTokenizer::nextToken(RString d)
{
   changed = true;
   delim = d;
   
   return nextToken();
}

vint StringTokenizer::skipDelims(vint start)
{
   vint pos = start;
   
   while(pos < maxPos)
   {
      vchar c = string->charAt(pos);
      if(!isDelim(c))
         break;
      pos++;
   }
   
   return pos;
}

vint StringTokenizer::scanTokens(vint start)
{
   vint pos = start;
   
   while(pos < maxPos)
   {
      vchar c = string->charAt(pos);
      if(isDelim(c))
         break;
      pos++;
   }
   
   return pos;
}

vbool StringTokenizer::isDelim(vchar c)
{
   return delim->indexOf(c) >= 0;
}

vbool StringTokenizer::hasMoreTokens()
{
   next = skipDelims(cur);
   return (next < maxPos);
}

RString StringTokenizer::nextToken()
{
   cur = (next >= 0 && !changed) ? next : skipDelims(cur);
   
   changed = false;
   next = -1;
   
   if(cur >= maxPos)
      return "";
   
   vint start = cur;
   cur = scanTokens(cur);
   
   return string->substring(start, cur);
}

vint StringTokenizer::tokensLeft()
{
   vint count = 0;
   vint current = cur;
   
   while(current < maxPos)
   {
      current = skipDelims(current);
      if(current >= maxPos)
         break;
      current = scanTokens(current);
      count++;
   }
   
   return count;
}

} /* namespace util */

} /* namespace aro */
