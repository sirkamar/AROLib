#ifndef CUI_BORDER_FRAMEBORDER_H
#define CUI_BORDER_FRAMEBORDER_H

#include <aro/cui/border/AbstractBorder.h>

namespace aro {

namespace cui {

namespace border {
class FrameBorder;
typedef Ref<FrameBorder> RFrameBorder;

class FrameBorder : public AbstractBorder
{
   public:
      virtual aws::RInsets getInsets(aws::RInsets insets);
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                              vint x, vint y, vint width, vint height);
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */

#endif /* CUI_BORDER_FRAMEBORDER_H */
