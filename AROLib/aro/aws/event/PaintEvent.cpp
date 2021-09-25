#include <aro/core.h>
#include <aro/aws/Component.h>
//#include <aro/aws/Rectangle.h>
#include <aro/aws/event/PaintEvent.h>

namespace aro {

namespace aws {

namespace event {

//const vint PaintEvent::PAINT = getNewID();
//
//const vint PaintEvent::UPDATE = getNewID();

PaintEvent::PaintEvent(RComponent source, vint id, RRectangle rect)
   :ComponentEvent(source, id)
{
   updateRect = rect;
}

void PaintEvent::setUpdateRect(RRectangle rect)
{
   updateRect = rect;
}

RRectangle PaintEvent::getUpdateRect()
{
   return updateRect;
}

RString PaintEvent::paramString()
{
   RString typeStr;
   
   if(eventID == PAINT)
      typeStr = "PAINT";
   
   else if(eventID == UPDATE)
      typeStr = "UPDATE";
   
   else
      typeStr = "unknown type";
   
   return typeStr; //+ ", updateRect=" + (updateRect != nullref ? updateRect->toString() : "null");
}

} /* namespace event */

} /* namespace aws */

} /* namespace aro */
