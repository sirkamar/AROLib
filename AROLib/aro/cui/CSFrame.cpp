#include <aro/cui/CSFrame.hpp>
#include <aro/aws/event/WindowEvent.hpp>

namespace aro {

namespace cui {

const vint CSFrame::CLOSE_ACTION_NOTHING = 0;
const vint CSFrame::CLOSE_ACTION_HIDE = 1;
const vint CSFrame::CLOSE_ACTION_DISPOSE = 2;
const vint CSFrame::CLOSE_ACTION_EXIT = 3;

CSFrame::CSFrame()
{
   
}

CSFrame::CSFrame(RString title)
   :Frame(title)
{
   defaultCloseAction = CLOSE_ACTION_DISPOSE;
}

vint CSFrame::getDefaultCloseAction()
{
   return defaultCloseAction;
}

void CSFrame::setDefaultCloseAction(vint action)
{
      if(action != CLOSE_ACTION_EXIT && action != CLOSE_ACTION_HIDE
         && action != CLOSE_ACTION_DISPOSE && action != CLOSE_ACTION_NOTHING)
         ex_throw new ArgumentException("defaultCloseAction must be one of: CLOSE_ACTION_EXIT, CLOSE_ACTION_HIDE, CLOSE_ACTION_DISPOSE, CLOSE_ACTION_NOTHING");
      
      defaultCloseAction = action;
}

void CSFrame::processWindowEvent(aws::event::RWindowEvent e)
{
   aws::Frame::processWindowEvent(e);
   
   if(e->getEventID() == aws::event::WindowEvent::WINDOW_CLOSING)
   {
      if(defaultCloseAction == CLOSE_ACTION_HIDE)
      {
         setVisible(false);
         e->consume();
      }
      else if(defaultCloseAction == CLOSE_ACTION_DISPOSE)
      {
         dispose();
         e->consume();
      }
      else if(defaultCloseAction == CLOSE_ACTION_EXIT)
      {
         System::exit(0);
      }
      else if(defaultCloseAction == CLOSE_ACTION_NOTHING)
      {
         
      }
   }
}

} /* nameapce cui */

} /* nameapce aro */
