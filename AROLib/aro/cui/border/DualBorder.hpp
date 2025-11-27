#ifndef CUI_BORDER_DUALBORDER_H
#define CUI_BORDER_DUALBORDER_H

#include <aro/cui/border/AbstractBorder.hpp>

namespace aro {

namespace cui {

namespace border {

class DualBorder;
typedef Ref<DualBorder> RDualBorder;

class DualBorder extends public AbstractBorder
{
   public:
      DualBorder();
      DualBorder(RAbstractBorder inside, RAbstractBorder outside);
      
      RAbstractBorder getInsideBorder();
      RAbstractBorder getOutsideBorder();

      aws::RInsets getInsets(aws::RInsets insets);
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                             vint x, vint y, vint width, vint height);
   
   protected:
      RAbstractBorder inside, outside;
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */

#endif /* CUI_BORDER_DUALBORDER_H */
