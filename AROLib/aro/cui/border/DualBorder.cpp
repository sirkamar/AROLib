#include <aro/core.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/Component.hpp>
#include <aro/cui/border/DualBorder.hpp>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

DualBorder::DualBorder()
{
   // default to null;
}

DualBorder::DualBorder(RAbstractBorder in, RAbstractBorder out)
{
   outside = out;
   inside = in;
}

RAbstractBorder DualBorder::getInsideBorder()
{
   return inside;
}

RAbstractBorder DualBorder::getOutsideBorder()
{
   return outside;
}

RInsets DualBorder::getInsets(RInsets insets)
{
   insets->set(0,0,0,0);

   if(outside != nullref)
   {
      RInsets temp = outside->getInsets();
      insets->top += temp->top;
      insets->left += temp->left;
      insets->right += temp->right;
      insets->bottom += temp->bottom;
   }
   
   if(inside != nullref)
   {
      RInsets temp = inside->getInsets();
      insets->top += temp->top;
      insets->left += temp->left;
      insets->right += temp->right;
      insets->bottom += temp->bottom;
   }
   
   return insets;
}

void DualBorder::paintBorder(RComponent c, RGraphics g,
                             vint x, vint y, vint width, vint height)
{
   vint px = x;
   vint py = y;
   vint pw = width;
   vint ph = height;
   RInsets tempInsets;
   
   if(outside != nullref)
   {
      outside->paintBorder(c, g, px, py, pw, ph);
      
      tempInsets = outside->getInsets();
      px += tempInsets->left;
      py += tempInsets->top;
      pw = pw - tempInsets->right - tempInsets->left;
      ph = ph - tempInsets->bottom - tempInsets->top;
   }
   
   if(inside != nullref)
      inside->paintBorder(c, g, px, py, pw, ph);
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
