#ifndef CUI_CSCHECKBOX_H
#define CUI_CSCHECKBOX_H

#include <aro/cui/CSAbstractButton.hpp>

namespace aro {

namespace cui {

class CSCheckBox;
typedef Ref<CSCheckBox> RCSCheckBox;

class CSCheckBox : public CSAbstractButton
{
   public:
      CSCheckBox();
      CSCheckBox(RString text);
      
      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getPreferredSize();
   
   protected:
      virtual void paintComponent(aws::RGraphics g);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSCHECKBOX_H */
