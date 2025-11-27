#ifndef AWS_GRAPHLAYOUT_H
#define AWS_GRAPHLAYOUT_H

#include <aro/aws/Container.hpp>

namespace aro {

namespace aws {

class GraphLayout;
typedef Ref<GraphLayout> RGraphLayout;

class GraphLayout extends public Object implements public Layout
{
   public:
	   GraphLayout();
      GraphLayout(vint rows,vint cols);
      GraphLayout(vint rows,vint cols,vint hgap,vint vgap);
      
      virtual RString toString();
      virtual void layoutContainer(RContainer target);
      virtual void removeLayoutComponent(RComponent comp);
      virtual RDimension recommendMaxSize(RContainer target);
      virtual RDimension recommendMinSize(RContainer target);
      virtual RDimension recommendPrefSize(RContainer target);
      virtual void addLayoutComponent(RComponent comp, RObject info);
   
   private:
      vint hgap, vgap, rows, cols;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_GRAPHLAYOUT_H */
