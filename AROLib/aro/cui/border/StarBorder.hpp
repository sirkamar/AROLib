#ifndef CUI_BORDER_STARBORDER_H
#define CUI_BORDER_STARBORDER_H

#include <aro/cui/border/AbstractBorder.hpp>

namespace aro {

namespace cui {

namespace border {

class StarBorder;
typedef Ref<StarBorder> RStarBorder;

class StarBorder : public AbstractBorder
{
   public:
      virtual aws::RInsets getInsets(aws::RInsets insets);

      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                             vint x, vint y, vint width, vint height);
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */

#endif /* CUI_BORDER_STARBORDER_H */
