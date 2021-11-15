#include <aro/core.hpp>
#include <aro/aws/Point.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/TideLayout.hpp>

namespace aro {

namespace aws {

TideLayout::TideLayout()
{
   hgap = vgap = 0;
}

TideLayout::TideLayout(vint hgap, vint vgap)
{
   thisref->hgap = hgap < 0 ? 0 : hgap;
   thisref->vgap = vgap < 0 ? 0 : vgap;
}

RString TideLayout::toString()
{
   return getType() + " [hgap:" + String::valueOf(hgap) +
          " vgap:" + String::valueOf(vgap) + "]";
}

void TideLayout::layoutContainer(RContainer target)
{
   RInsets insets = target->getInsets();
   RDimension dim = target->getSize();
   
   vint maxwidth = dim->width - (insets->left + insets->right + hgap*2);
   vint x = 0, y = insets->top + vgap, row = 0, start = 0;
   vint members = target->getComponentCount();
   
   for(vint i=0; i<members; i++)
   {
      RComponent m = target->getComponent(i);
      if(m->isVisible())
      {
         RDimension d = m->getPreferredSize();
         m->setSize(d->width, d->height);
         
         if(x == 0 || x+d->width <= maxwidth)
         {
            if(x > 0)
            x += hgap;
            x += d->width;
            row = Math::maximum(row, d->height);
         }
         else
         {
            moveComponents(target, insets->left + hgap, y, maxwidth - x, row, start, i);
            x = d->width;
            y += vgap + row;
            row = d->height;
            start = i;
         }
      }
   }
   moveComponents(target, insets->left + hgap, y, maxwidth - x, row, start, members);
}

void TideLayout::removeLayoutComponent(RComponent)
{
   
}

RDimension TideLayout::recommendMaxSize(RContainer target)
{
   return target->Component::getMaximumSize();
}

RDimension TideLayout::recommendMinSize(RContainer target)
{
   RDimension dim = new Dimension();
   vint nmembers = target->getComponentCount();
   
   for(vint i = 0; i < nmembers; i++)
   {
      RComponent m = target->getComponent(i);
      if(m->isVisible())
      {
         RDimension d = m->getMinimumSize();
         dim->height = Math::maximum(dim->height, d->height);
         if(i > 0)
            dim->width += hgap;
         
         dim->width += d->width;
      }
   }
   
   RInsets insets = target->getInsets();
   dim->width += insets->left + insets->right + hgap*2;
   dim->height += insets->top + insets->bottom + vgap*2;
   
   return dim;
}

RDimension TideLayout::recommendPrefSize(RContainer target)
{
   RDimension dim = new Dimension();
   vint nmembers = target->getComponentCount();
   vbool firstVisibleComponent = true;
   
   for(vint i = 0; i < nmembers; i++)
   {
      RComponent m = target->getComponent(i);
      if(m->isVisible())
      {
         RDimension d = m->getPreferredSize();
         dim->height = Math::maximum(dim->height, d->height);
         if(firstVisibleComponent)
            firstVisibleComponent = false;
         else
            dim->width += hgap;
         dim->width += d->width;
      }
   }
   
   RInsets insets = target->getInsets();
   dim->width += insets->left + insets->right + hgap*2;
   dim->height += insets->top + insets->bottom + vgap*2;
   
   return dim;
}

void TideLayout::addLayoutComponent(RComponent, RObject)
{
   
}

void TideLayout::moveComponents(RContainer target, vint x, vint y, vint width,
                                       vint height, vint rowStart, vint rowEnd)
{
   x += width / 2;
   RPoint pnt = target->getLocation();
   for(vint i = rowStart; i < rowEnd; i++)
   {
      RComponent m = target->getComponent(i);
      RDimension dim = m->getSize();
      if(m->isVisible())
      {
         m->setLocation(pnt->x + x, pnt->y + y + (height - dim->height) / 2);
         x += dim->width + hgap;
      }
   }
}

} /* namespace aws */

} /* namespace aro */
