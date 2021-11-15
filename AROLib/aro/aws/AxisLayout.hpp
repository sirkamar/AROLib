#ifndef AWS_AXISLAYOUT_H
#define AWS_AXISLAYOUT_H

#include <aro/aws/Layout.hpp>

namespace aro {

namespace aws {

class AxisLayout;
typedef Ref<AxisLayout> RAxisLayout;

class AxisLayout : public Object, public Layout
{
   public:
      static const vint X_AXIS;
      static const vint Y_AXIS;
      
      AxisLayout();
      AxisLayout(vint axis);
      
      RString toString();
      void layoutContainer(RContainer target);
      void removeLayoutComponent(RComponent comp);
      RDimension recommendMaxSize(RContainer target);
      RDimension recommendMinSize(RContainer target);
      RDimension recommendPrefSize(RContainer target);
      void addLayoutComponent(RComponent comp, RObject info);
   
   private:
      vint axis;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_AXISLAYOUT_H */
