#ifndef CUI_CSFRAME_H
#define CUI_CSFRAME_H

#include <aro\aws\Frame.hpp>

namespace aro {

namespace cui {

class CSFrame;
typedef Ref<CSFrame> RCSFrame;

class CSFrame extends public aws::Frame
{
   public:
      CSFrame();
      CSFrame(RString title);

      vint getDefaultCloseAction();
      void setDefaultCloseAction(vint action);

      static const vint CLOSE_ACTION_EXIT;
      static const vint CLOSE_ACTION_HIDE;
      static const vint CLOSE_ACTION_DISPOSE;
      static const vint CLOSE_ACTION_NOTHING;

   protected:
      virtual void processWindowEvent(aws::event::RWindowEvent e);
   
   private:
      vint defaultCloseAction;
   
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSFRAME_H */
