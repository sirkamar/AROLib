#ifndef CUI_BORDER_ABSTRACTBORDER_H
#define CUI_BORDER_ABSTRACTBORDER_H

#include <aro/cui/border/Border.hpp>

namespace aro {

namespace cui {

namespace border {

class AbstractBorder;
typedef Ref<AbstractBorder> RAbstractBorder;

class AbstractBorder : public Object, public Border
{
   public:
      AbstractBorder();
      
      virtual aws::RInsets getInsets();

      virtual aws::RInsets getInsets(aws::RInsets insets)=0;
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g);
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                              vint x, vint y, vint width, vint height)=0;
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */

#endif /* CUI_BORDER_ABSTRACTBORDER_H */
