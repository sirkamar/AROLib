#ifndef CUI_BORDER_EMPTYBORDER_H
#define CUI_BORDER_EMPTYBORDER_H

#include <aro/cui/border/AbstractBorder.hpp>

namespace aro {

namespace cui {

namespace border {

class EmptyBorder;
typedef Ref<EmptyBorder> REmptyBorder;

class EmptyBorder extends public AbstractBorder
{
   public:
      EmptyBorder(aws::RInsets insets);
      
      EmptyBorder(vint top, vint left, vint right, vint bottom);
      
      virtual aws::RInsets getInsets(aws::RInsets insets);
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                             vint x, vint y, vint width, vint height);
   
   protected:
      vint left, right, top, bottom;
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */

#endif /* CUI_BORDER_EMPTYBORDER_H */
