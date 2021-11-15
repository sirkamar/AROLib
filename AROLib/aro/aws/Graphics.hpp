#ifndef AWS_GRAPHICS_H
#define AWS_GRAPHICS_H

#include <aro/core/Interface.hpp>

namespace aro {

namespace aws {

class Component;
interface Graphics;
typedef Ref<Graphics> RGraphics;
typedef Ref<Component> RComponent;

/** The graphics interface defines the functions that
  * each graphics object will be required to provide.
  * Each GUI type will need to provide its own
  * graphics implementation to enable visual
  * output (i.e. drawing) of components. */
interface Graphics : Interface
{
   virtual void clear()=0;
   virtual void initBounds(RComponent comp)=0;
   virtual void drawString(vint x, vint y, RString str)=0;
   virtual void drawVerticalLine(vint x, vint y, vint len)=0;
   virtual void drawHorizontalLine(vint x, vint y, vint len)=0;
   virtual void drawRectangle(vint x, vint y, vint width, vint height)=0;
   virtual void clearRectangle(vint x, vint y, vint width, vint height)=0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_GRAPHICS_H */
