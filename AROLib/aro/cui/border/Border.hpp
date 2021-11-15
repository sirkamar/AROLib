#ifndef CUI_BORDER_BORDER_H
#define CUI_BORDER_BORDER_H

#include <aro/core.hpp>

namespace aro {

namespace aws {

class Insets;
class Component;
interface Graphics;
typedef Ref<Insets> RInsets;
typedef Ref<Graphics> RGraphics;
typedef Ref<Component> RComponent;

}

namespace cui {

namespace border {

interface Border;
typedef Ref<Border> RBorder;

interface Border : Interface
{
   public:
      virtual aws::RInsets getInsets()=0;

      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g)=0;

      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                               vint x, vint y, vint width, vint height)=0;
};

} /* namespace border */

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_BORDER_BORDER_H */
