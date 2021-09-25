#include <aro/core.h>
#include <aro/aws/Point.h>
#include <aro/aws/Insets.h>
#include <aro/aws/ZoneLayout.h>

namespace aro {

namespace aws {

const RString ZoneLayout::BOTTOM = "BOTTOM";
const RString ZoneLayout::MIDDLE = "MIDDLE";
const RString ZoneLayout::RIGHT = "RIGHT";
const RString ZoneLayout::LEFT = "LEFT";
const RString ZoneLayout::TOP = "TOP";

ZoneLayout::ZoneLayout()
{
   hgap = vgap = 0;
}

ZoneLayout::ZoneLayout(vint hgap, vint vgap)
{
   thisref->hgap = hgap < 0 ? 0 : hgap;
   thisref->vgap = vgap < 0 ? 0 : vgap;
}

RString ZoneLayout::toString()
{
   return getType() + " [hgap:" + String::valueOf(hgap) +
          " vgap:" + String::valueOf(vgap) + "]";
}

void ZoneLayout::layoutContainer(RContainer target)
{
   RDimension dim = target->getSize();
   RPoint pnt = target->getLocation();
   RInsets insets = target->getInsets();
   vint nrth = pnt->y+insets->top, sth = pnt->y+dim->height-insets->bottom;
   vint west = pnt->x+insets->left, east = pnt->x+dim->width-insets->right-1;
   
   RComponent c;
   if((c=getChild(TOP)) != nullref)
   {
      RDimension cd = c->getSize();
      c->setSize(east-west+1, cd->height);
      RDimension d = c->getPreferredSize();
      c->setSize(east-west+1, d->height);
      c->setLocation(west, nrth);
      nrth += d->height + vgap + 1;
   }
   
   if((c=getChild(BOTTOM)) != nullref)
   {
      RDimension cd = c->getSize();
      c->setSize(east-west+1, cd->height);
      RDimension d = c->getPreferredSize();
      c->setLocation(west, sth-d->height);
      c->setSize(east-west+1, d->height);
      sth -= d->height + vgap + 1;
   }
   
   if((c=getChild(RIGHT)) != nullref)
   {
      RDimension cd = c->getSize();
      c->setSize(cd->width, sth-nrth+1);
      RDimension d = c->getPreferredSize();
      c->setLocation(east-d->width, nrth);
      c->setSize(d->width, sth-nrth+1);
      east -= d->width + hgap + 1;
   }
   
   if((c=getChild(LEFT)) != nullref)
   {
      RDimension cd = c->getSize();
      c->setSize(cd->width, sth-nrth+1);
      RDimension d = c->getPreferredSize();
      c->setSize(d->width, sth-nrth+1);
      c->setLocation(west, nrth);
      west += d->width + hgap + 1;
   }
   
   if((c=getChild(MIDDLE)) != nullref)
   {
      c->setLocation(west, nrth);
      c->setSize(east-west+1, sth-nrth+1);
   }
}

void ZoneLayout::removeLayoutComponent(RComponent comp)
{
   if(comp == middle)
      middle = nullref;
   else if(comp == top)
      top = nullref;
   else if(comp == left)
      left = nullref;
   else if(comp == right)
      right = nullref;
   else if(comp == bottom)
      bottom = nullref;
}

RDimension ZoneLayout::recommendMaxSize(RContainer target)
{
   return target->Component::getMaximumSize();
}

RDimension ZoneLayout::recommendMinSize(RContainer target)
{
   RComponent c;
   RDimension dim = new Dimension();;
   
   if((c=getChild(RIGHT)) != nullref)
   {
      RDimension d = c->getMinimumSize();
      dim->width += d->width + hgap;
      dim->height = Math::maximum(d->height, dim->height);
   }
   if((c=getChild(LEFT)) != nullref)
   {
      RDimension d = c->getMinimumSize();
      dim->width += d->width + hgap;
      dim->height = Math::maximum(d->height, dim->height);
   }
   if((c=getChild(MIDDLE)) != nullref)
   {
      RDimension d = c->getMinimumSize();
      dim->width += d->width;
      dim->height = Math::maximum(d->height, dim->height);
   }
   if((c=getChild(TOP)) != nullref)
   {
      RDimension d = c->getMinimumSize();
      dim->width = Math::maximum(d->width, dim->width);
      dim->height += d->height + vgap;
   }
   if((c=getChild(BOTTOM)) != nullref)
   {
      RDimension d = c->getMinimumSize();
      dim->width = Math::maximum(d->width, dim->width);
      dim->height += d->height + vgap;
   }
   
   RInsets insets = target->getInsets();
   dim->width += insets->left + insets->right;
   dim->height += insets->top + insets->bottom;
   
   return dim;
}

RDimension ZoneLayout::recommendPrefSize(RContainer target)
{
   RComponent c;
   RDimension dim = new Dimension();
   
   if((c=getChild(RIGHT)) != nullref)
   {
      RDimension d = c->getPreferredSize();
      dim->width += d->width + hgap;
      dim->height = Math::maximum(d->height, dim->height);
   }
   if((c=getChild(LEFT)) != nullref)
   {
      RDimension d = c->getPreferredSize();
      dim->width += d->width + hgap;
      dim->height = Math::maximum(d->height, dim->height);
   }
   if((c=getChild(MIDDLE)) != nullref)
   {
      RDimension d = c->getPreferredSize();
      dim->width += d->width;
      dim->height = Math::maximum(d->height, dim->height);
   }
   if((c=getChild(TOP)) != nullref)
   {
      RDimension d = c->getPreferredSize();
      dim->width = Math::maximum(d->width, dim->width);
      dim->height += d->height + vgap;
   }
   if((c=getChild(BOTTOM)) != nullref)
   {
      RDimension d = c->getPreferredSize();
      dim->width = Math::maximum(d->width, dim->width);
      dim->height += d->height + vgap;
   }
   
   RInsets insets = target->getInsets();
   dim->width += insets->left + insets->right;
   dim->height += insets->top + insets->bottom;
   
   return dim;
}

void ZoneLayout::addLayoutComponent(RComponent comp, RObject info)
{
   if(!type_of<String>(info))
      return;
   
   if(info->equals(TOP))
      top = comp;
   else if(info->equals(LEFT))
      left = comp;
   else if(info->equals(RIGHT))
      right = comp;
   else if(info->equals(BOTTOM))
      bottom = comp;
   else //if(info->equals(MIDDLE))
      middle = comp;
}

RComponent ZoneLayout::getChild(RString key)
{
   RComponent result;
   
   if(key->equals(MIDDLE))
      result = middle;
   else if(key->equals(TOP))
      result = top;
   else if(key->equals(LEFT))
      result = left;
   else if(key->equals(RIGHT))
      result = right;
   else if(key->equals(BOTTOM))
      result = bottom;
   
   if(result != nullref && !result->isVisible())
      result = nullref;
   
   return result;
}

} /* namespace aws */

} /* namespace aro */
