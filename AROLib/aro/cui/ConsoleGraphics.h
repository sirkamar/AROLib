#ifndef CUI_CONSOLEGRAPHICS_H
#define CUI_CONSOLEGRAPHICS_H

#include <aro/core/String.h>
#include <aro/aws/Graphics.h>

namespace aro {

namespace aws {

namespace event {
class PaintEvent;
typedef Ref<PaintEvent> RPaintEvent;
}

}

namespace cui {

class ConsoleGraphics;
typedef Ref<ConsoleGraphics> RConsoleGraphics;

class ConsoleGraphics : public Object, public aws::Graphics
{
   public:
      ConsoleGraphics(aws::event::RPaintEvent e);
      
      virtual void clear();
      virtual vchar getEdgeChar();
      virtual vchar getVerticalChar();
      virtual vchar getHorizontalChar();
      virtual void setEdgeChar(vchar e);
      virtual void setVerticalChar(vchar v);
      virtual void setHorizontalChar(vchar h);
      virtual void initBounds(aws::RComponent comp);
      virtual void drawString(vint x,vint y,RString str);
      virtual void drawVerticalLine(vint x,vint y,vint len);
      virtual void drawHorizontalLine(vint x,vint y,vint len);
      virtual void setDrawingChars(vchar edge,vchar vert,vchar horz);
      virtual void drawRectangle(vint x,vint y,vint width,vint height);
      virtual void clearRectangle(vint x, vint y, vint width, vint height);
   
   private:
      vbool shown;
      vchar corner, horz, vert;
      vint top, left, right, bottom;
      
      void initBounds(aws::RComponent comp, aws::RRectangle bounds);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CONSOLEGRAPHICS_H */
