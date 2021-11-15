#ifndef AWS_TIDELAYOUT_H
#define AWS_TIDELAYOUT_H

#include <aro/aws/Container.hpp>

namespace aro {

namespace aws {

class TideLayout;
typedef Ref<TideLayout> RTideLayout;

class TideLayout : public Object, public Layout
{
   public:
	   TideLayout();
      TideLayout(vint hgap,vint vgap);
      
      virtual RString toString();
      virtual void layoutContainer(RContainer target);
      virtual void removeLayoutComponent(RComponent comp);
      virtual RDimension recommendMaxSize(RContainer target);
      virtual RDimension recommendMinSize(RContainer target);
      virtual RDimension recommendPrefSize(RContainer target);
      virtual void addLayoutComponent(RComponent comp, RObject info);
   
   private:
      vint hgap, vgap;
      
      void moveComponents(RContainer,vint,vint,vint,vint,vint,vint);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_TIDELAYOUT_H */
