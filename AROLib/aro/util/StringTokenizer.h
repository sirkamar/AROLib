#ifndef UTIL_STRINGTOKENIZER_H
#define UTIL_STRINGTOKENIZER_H

#include <aro/core.h>

namespace aro {

namespace util {

class StringTokenizer;
typedef Ref<StringTokenizer> RStringTokenizer;

class StringTokenizer : public Object
{
   public:
      StringTokenizer(RString str);
      StringTokenizer(RString str, RString delim);
      
      RString nextToken(RString delim);
      vbool hasMoreTokens();
      RString nextToken();
      vint tokensLeft();
   
   private:
      vint cur;
      vint next;
      vint maxPos;
      vbool changed;
      RString delim;
      RString string;
      
      vint skipDelims(vint);
      vint scanTokens(vint);
      vbool isDelim(vchar);
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_STRINGTOKENIZER_H */
