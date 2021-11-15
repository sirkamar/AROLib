#ifndef CUI_CONSOLE_H
#define CUI_CONSOLE_H

#include <aro/core.hpp>

namespace aro {

namespace aws {
class Dimension;
typedef Ref<Dimension> RDimension;
}

namespace cui {

class Console final : public Object
{
   public:
      static void clear();
      static void putChar(vchar c);
      static aws::RDimension getSize();
      static void putString(RString str);
      static void moveCursor(vint x,vint y);
   
   private:
      Console();
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CONSOLE_H */
