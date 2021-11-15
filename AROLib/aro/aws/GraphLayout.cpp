#include <aro/core.hpp>
#include <aro/aws/Point.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/GraphLayout.hpp>

namespace aro {

namespace aws {

GraphLayout::GraphLayout()
{
   rows = cols = 0;
   hgap = vgap = 0;
}

GraphLayout::GraphLayout(vint rows, vint cols)
{
   thisref->rows = rows < 0 ? 0 : rows;
   thisref->cols = cols < 0 ? 0 : cols;
   hgap = vgap = 0;
}

GraphLayout::GraphLayout(vint rows, vint cols, vint hgap, vint vgap)
{
   thisref->rows = rows < 0 ? 0 : rows;
   thisref->cols = cols < 0 ? 0 : cols;
   thisref->hgap = hgap < 0 ? 0 : hgap;
   thisref->vgap = vgap < 0 ? 0 : vgap;
}

RString GraphLayout::toString()
{
   return getType() + " [rows:" + String::valueOf(rows) +
          " cols:" + String::valueOf(cols) + " hgap:" +
          String::valueOf(hgap) + " vgap:" +
          String::valueOf(vgap) + "]";
}

void GraphLayout::layoutContainer(RContainer target)
{
   vint ncomponents = target->getComponentCount();
   RInsets insets = target->getInsets();
   vint nrows = rows; vint ncols = cols;
   RDimension dim = target->getSize();
   RPoint pnt = target->getLocation();
   
   if(ncomponents == 0)
      return;
   
   if(nrows > 0)
      ncols = (ncomponents + nrows - 1) / nrows;
   else
      nrows = (ncomponents + ncols - 1) / ncols;
   
   vint w = dim->width - (insets->left + insets->right);
   vint h = dim->height - (insets->top + insets->bottom);
   w = (w - (ncols - 1) * hgap) / ncols;
   h = (h - (nrows - 1) * vgap) / nrows;
   
   for(vint c = 0, x = pnt->x+insets->left; c < ncols; c++, x += w + hgap)
   {
      for(vint r = 0, y = pnt->y+insets->top; r < nrows; r++, y += h + vgap)
      {
         vint i = r * ncols + c;
         if (i < ncomponents)
         {
            RComponent cmp = target->getComponent(i);
            cmp->setLocation(x, y);
            cmp->setSize(w, h);
         }
      }
   }
}

void GraphLayout::removeLayoutComponent(RComponent)
{
   
}

RDimension GraphLayout::recommendMaxSize(RContainer target)
{
   return target->Component::getMaximumSize();
}

RDimension GraphLayout::recommendMinSize(RContainer target)
{
   vint ncomponents = target->getComponentCount();
   RInsets insets = target->getInsets();
   vint nrows = rows, ncols = cols;

   if(nrows > 0)
      ncols = (ncomponents + nrows - 1) / nrows;
   else
      nrows = (ncomponents + ncols - 1) / ncols;
   
   vint w = 0, h = 0;
   for(vint i = 0; i < ncomponents; i++)
   {
      RComponent comp = target->getComponent(i);
      RDimension d = comp->getMinimumSize();
      if(w < d->width)
         w = d->width;
      
      if(h < d->height)
         h = d->height;
   }
   return new Dimension(insets->left + insets->right + ncols*w + (ncols-1)*hgap,
          insets->top + insets->bottom + nrows*h + (nrows-1)*vgap);
}

RDimension GraphLayout::recommendPrefSize(RContainer target)
{
   vint ncomponents = target->getComponentCount();
   RInsets insets = target->getInsets();
   vint nrows = rows, ncols = cols;
   
   if(nrows > 0)
      ncols = (ncomponents + nrows - 1) / nrows;
   else
      nrows = (ncomponents + ncols - 1) / ncols;
   
   vint w = 0, h = 0;
   for (vint i = 0; i < ncomponents; i++)
   {
      RComponent comp = target->getComponent(i);
      RDimension d = comp->getPreferredSize();
      if(w < d->width)
         w = d->width;
      
      if(h < d->height)
         h = d->height;
   }
   return new Dimension(insets->left + insets->right + ncols*w + (ncols-1)*hgap,
          insets->top + insets->bottom + nrows*h + (nrows-1)*vgap);
}

void GraphLayout::addLayoutComponent(RComponent, RObject)
{
   
}

} /* namespace aws */

} /* namespace aro */
