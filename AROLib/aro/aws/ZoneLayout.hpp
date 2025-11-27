#ifndef AWS_ZONELAYOUT_H
#define AWS_ZONELAYOUT_H

#include <aro/aws/Container.hpp>

namespace aro {

namespace aws {

class ZoneLayout;
typedef Ref<ZoneLayout> RZoneLayout;

class ZoneLayout extends public Object implements public Layout
{
   public:
      static const RString TOP;
      static const RString LEFT;
      static const RString RIGHT;
      static const RString BOTTOM;
      static const RString MIDDLE;
      
      ZoneLayout();
      ZoneLayout(vint hgap,vint vgap);
      
      virtual RString toString();
      virtual void layoutContainer(RContainer target);
      virtual void removeLayoutComponent(RComponent comp);
      virtual RDimension recommendMaxSize(RContainer target);
      virtual RDimension recommendMinSize(RContainer target);
      virtual RDimension recommendPrefSize(RContainer target);
      virtual void addLayoutComponent(RComponent comp, RObject info);
   
   private:
      vint hgap, vgap;
      RComponent middle;
      RComponent top, bottom;
      RComponent left, right;
      
      RComponent getChild(RString zone);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_ZONELAYOUT_H */
