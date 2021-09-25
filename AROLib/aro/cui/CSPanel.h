#ifndef CUI_CSPANEL_H
#define CUI_CSPANEL_H

#include <aro/cui/CSComponent.h>

namespace aro {

namespace cui {

class CSPanel;
typedef Ref<CSPanel> RCSPanel;

class CSPanel : public CSComponent
{
   public:
      CSPanel();
      CSPanel(aws::RLayout l);
   
   protected:
      virtual void paintComponent(aws::RGraphics g);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSPANEL_H */
