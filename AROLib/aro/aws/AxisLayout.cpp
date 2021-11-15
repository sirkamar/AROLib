#include <aro/core.hpp>
#include <aro/aws/Point.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/Dimension.hpp>
#include <aro/aws/Container.hpp>
#include <aro/aws/AxisLayout.hpp>

namespace aro {

namespace aws {

const vint AxisLayout::X_AXIS = 1;
const vint AxisLayout::Y_AXIS = 2;

AxisLayout::AxisLayout()
{
   axis = Y_AXIS;
}

AxisLayout::AxisLayout(vint axis)
{
   thisref->axis = axis == X_AXIS ? X_AXIS : Y_AXIS;
}

RString AxisLayout::toString()
{
   return getType() + " [Axis:" +
          (axis == X_AXIS ? "X_AXIS" :
          "Y_AXIS") + "]";
}

void AxisLayout::layoutContainer(RContainer target)
{
   vint ncomponents = target->getComponentCount();
   RInsets insets = target->getInsets();
   RDimension dim = target->getSize();
   RPoint pnt = target->getLocation();
   vint width = 0, height = 0;
   
   if(axis == X_AXIS)
      height = dim->height - (insets->top + insets->bottom);
   else
      width = dim->width - (insets->left + insets->right);
   
   for(vint i=0; i<ncomponents; i++)
   {
      RComponent m = target->getComponent(i);
      if(m->isVisible())
      {
         RDimension d = m->getPreferredSize();
         if(axis == X_AXIS)
         {
            m->setLocation(pnt->x+insets->left+width, pnt->y+insets->top);
            m->setSize(d->width, height);
            width += d->width;
         }
         else
         {
            
            m->setLocation(pnt->x+insets->left, pnt->y+insets->top+height);
            m->setSize(width, d->height);
            height += d->height;
         }
      }
   }
}

void AxisLayout::removeLayoutComponent(RComponent)
{
   
}

RDimension AxisLayout::recommendMaxSize(RContainer target)
{
   return target->Component::getMaximumSize();
}

RDimension AxisLayout::recommendMinSize(RContainer target)
{
   vint ncomponents = target->getComponentCount();
   RDimension dim = target->getSize();
   vint width = 0, height = 0;
   
   if(axis == X_AXIS)
      height = dim->height;
   else
      width = dim->width;
   
   for(vint i=0; i<ncomponents; i++)
   {
      RComponent m = target->getComponent(i);
      if(m->isVisible())
      {
         RDimension d = m->getMinimumSize();
         if(axis == X_AXIS)
            width += d->width;
         else
            height += d->height;
      }
   }
   
   RInsets insets = target->getInsets();
   width += insets->left + insets->right;
   height += insets->top + insets->bottom;
   
   return new Dimension(width,height);
}

RDimension AxisLayout::recommendPrefSize(RContainer target)
{
   vint ncomponents = target->getComponentCount();
   RDimension dim = target->getSize();
   vint width = 0, height = 0;
   
   if(axis == X_AXIS)
      height = dim->height;
   else
      width = dim->width;
   
   for(vint i=0; i<ncomponents; i++)
   {
      RComponent m = target->getComponent(i);
      if(m->isVisible())
      {
         RDimension d = m->getPreferredSize();
         if(axis == X_AXIS)
         {
            width += d->width;
            
            if(height < d->height)
               height = d->height;
         }
         else
         {
            height += d->height;
            
            if(width < d->width)
               width = d->width;
         }
      }
   }
   
   RInsets insets = target->getInsets();
   width += insets->left + insets->right;
   height += insets->top + insets->bottom;
   
   return new Dimension(width,height);
}

void AxisLayout::addLayoutComponent(RComponent, RObject)
{
   
}

} /* namespace aws */

} /* namespace aro */
