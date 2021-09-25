#include <aro/core.h>
#include <aro/aws/Insets.h>
#include <aro/aws/Graphics.h>
#include <aro/aws/Dimension.h>
#include <aro/aws/Component.h>
#include <aro/cui/border/FrameBorder.h>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

RInsets FrameBorder::getInsets(RInsets insets)
{
   insets->set(3, 1, 1, 1);
   return insets;
}

void FrameBorder::paintBorder(RComponent comp, RGraphics g,
                              vint x, vint y, vint width, vint height)
{
   g->drawHorizontalLine(x+1, y+2, width-2);
   
   g->drawRectangle(x, y, width, height);
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
