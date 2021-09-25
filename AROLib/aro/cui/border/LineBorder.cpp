#include <aro/core.h>
#include <aro/aws/Insets.h>
#include <aro/aws/Graphics.h>
#include <aro/aws/Dimension.h>
#include <aro/aws/Component.h>
#include <aro/cui/border/LineBorder.h>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

LineBorder::LineBorder()
{
   thickness = 1;
}

LineBorder::LineBorder(vint thick)
{
   thickness = thick;
}

vint LineBorder::getThickness()
{
   return thickness;
}

RInsets LineBorder::getInsets(RInsets insets)
{
   insets->set(thickness, thickness, thickness, thickness);
   return insets;
}

void LineBorder::paintBorder(RComponent comp, RGraphics g,
                            vint x, vint y, vint width, vint height)
{
   for(vint i=0; i<thickness; i++)
      g->drawRectangle(x+i, y+i, width-i-i, height-i-i);
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
