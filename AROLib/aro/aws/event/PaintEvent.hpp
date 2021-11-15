#ifndef AWSE_PAINTEVENT_H
#define AWSE_PAINTEVENT_H

#include <aro/aws/Rectangle.hpp>
#include <aro/aws/event/ComponentEvent.hpp>

namespace aro {

namespace aws {

namespace event {

class PaintEvent;
typedef Ref<PaintEvent> RPaintEvent;

class PaintEvent : public ComponentEvent
{
   public:
      static const vint PAINT    = 1001014;
      static const vint UPDATE   = 1001015;
      
      PaintEvent(RComponent source, vint id, RRectangle updateRect);
      virtual void setUpdateRect(RRectangle updateRect);
      virtual RRectangle getUpdateRect();
      virtual RString paramString();
   
   private:
      RRectangle updateRect;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_PAINTEVENT_H */
