#ifndef AWS_LINEBORDER_H
#define AWS_LINEBORDER_H

#include <aro/cui/border/AbstractBorder.hpp>

namespace aro {

namespace cui {

namespace border {

class LineBorder;
typedef Ref<LineBorder> RLineBorder;

class LineBorder : public AbstractBorder
{
   public:
      LineBorder();

      LineBorder(vint thickness);
      
      virtual vint getThickness();

      virtual aws::RInsets getInsets(aws::RInsets insets);
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                              vint x, vint y, vint width, vint height);
   
   protected:
      vint thickness;
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_LINEBORDER_H */
