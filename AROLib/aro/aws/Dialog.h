#ifndef AWS_DIALOG_H
#define AWS_DIALOG_H

#include <aro/aws/Window.h>

namespace aro {

namespace aws {

class Dialog;
typedef Ref<Dialog> RDialog;

class Dialog : public Window
{
   public:
      Dialog();
      
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_DIALOG_H */
