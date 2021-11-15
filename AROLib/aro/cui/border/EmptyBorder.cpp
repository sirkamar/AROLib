#include <aro/core.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/Component.hpp>
#include <aro/cui/border/EmptyBorder.hpp>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

EmptyBorder::EmptyBorder(RInsets insets)
{
   top = insets->top;
   left = insets->left;
   right = insets->right;
   bottom = insets->bottom;
}

EmptyBorder::EmptyBorder(vint t, vint l, vint r, vint b)
{
   top = t;
   left = l;
   right = r;
   bottom = b;
}

RInsets EmptyBorder::getInsets(RInsets insets)
{
   insets->set(top, left, bottom, right);
   return insets;
}

void EmptyBorder::paintBorder(RComponent c, RGraphics g,
                             vint x, vint y, vint width, vint height)
{
   // Does no drawing by default.
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
