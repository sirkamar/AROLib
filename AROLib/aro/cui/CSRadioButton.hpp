#ifndef CUI_CSRADIOBUTTON_H
#define CUI_CSRADIOBUTTON_H

#include <aro/cui/CSAbstractButton.hpp>

namespace aro {

namespace cui {

class CSRadioButton;
typedef Ref<CSRadioButton> RCSRadioButton;

class CSRadioButton extends public CSAbstractButton
{
   public:
      CSRadioButton();
      CSRadioButton(RString text);
      
      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getPreferredSize();
   
   protected:
      virtual void paintComponent(aws::RGraphics g);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSRADIOBUTTON_H */