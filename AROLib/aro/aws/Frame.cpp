#include <aro/core.hpp>
#include <aro/aws/Frame.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/event/KeyEvent.hpp>

namespace aro {

namespace aws {

Frame::Frame()
   :Frame("untitled")
{
   
}

Frame::Frame(RString title)
   :Frame(nullref, title)
{
   
}

Frame::Frame(RWindow owner)
   :Frame(owner, "untitled")
{

}

Frame::Frame(RWindow owner, RString text)
   :Window(owner), title(text == nullref ? "" : text)
{
   
}

void Frame::setTitle(RString text)
{
   RString oldTiltle = text;
   
   if(text == nullref)
      text = "";
   
   sync_lock(thisref)
   {
      title = text;
   }

   firePropertyChanged("title", oldTiltle, title);
}

RString Frame::getTitle()
{
   return title;
}

void Frame::postProcessKeyEvent(event::RKeyEvent e)
{
   //if(menuBar != nullref && menuBar->handleShortcut(e))
   //{
   //   e->consume();
   //   return;
   //}
   
   Window::postProcessKeyEvent(e);
}

RInsets Frame::getInsets()
{
   return new Insets(3, 1, 1, 1);
}

void Frame::paint(RGraphics g)
{
   g->drawString(1, 1, title);
   
   g->drawHorizontalLine(1, 2, getWidth() - 2);
   
   g->drawRectangle(0, 0, getWidth(), getHeight());
   
   Window::paint(g); // paint the frame's children
}

} /* namespace aws */

} /* namespace aro */
