#ifndef AWS_LAYOUT_H
#define AWS_LAYOUT_H

#include <aro/core.h>

namespace aro {

namespace aws {

class Dimension;
class Component;
class Container;
interface Layout;

// reference type definitions
typedef Ref<Layout> RLayout;
typedef Ref<Dimension> RDimension;
typedef Ref<Component> RComponent;
typedef Ref<Container> RContainer;

/** A Layout is a scheme for arranging
 * components within a container. */
interface Layout : Interface
{
   virtual void layoutContainer(RContainer target)=0;
   virtual void removeLayoutComponent(RComponent comp)=0;
   virtual RDimension recommendMaxSize(RContainer target)=0;
   virtual RDimension recommendMinSize(RContainer target)=0;
   virtual RDimension recommendPrefSize(RContainer target)=0;
   virtual void addLayoutComponent(RComponent comp, RObject info)=0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_LAYOUT_H */
