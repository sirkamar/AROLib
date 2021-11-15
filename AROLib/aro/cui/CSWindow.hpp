#ifndef CUI_CSWINDOW_H
#define CUI_CSWINDOW_H

#include <aro\aws\Window.hpp>

namespace aro {

namespace cui {

class CSWindow;
typedef Ref<CSWindow> RCSWindow;

class CSWindow :  public aws::Window
{
   public:
      CSWindow();
      CSWindow(aws::RWindow owner);
   
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSWINDOW_H */
