#ifndef CUI_CSBUTTON_H
#define CUI_CSBUTTON_H

#include <aro/cui/CSAbstractButton.hpp>

namespace aro {

namespace cui {

class CSButton;
typedef Ref<CSButton> RCSButton;

class CSButton : public CSAbstractButton
{
   public:
      CSButton();
      CSButton(RString str);
   
   protected:
      virtual void paintComponent(aws::RGraphics g);
      
      void processComponentKeyEvent(aws::event::RKeyEvent e);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSBUTTON_H */
