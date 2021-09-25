#ifndef CUI_CSPASSWORDBOX_H
#define CUI_CSPASSWORDBOX_H

#include <aro/cui/CSTextBox.h>

namespace aro {

namespace cui {

class CSPasswordBox;
typedef Ref<CSPasswordBox> RCSPasswordBox;

class CSPasswordBox : public CSTextBox
{
   public:
      CSPasswordBox();
      CSPasswordBox(vint width);
      CSPasswordBox(RString text);
      CSPasswordBox(RString text,vint width);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSPASSWORDBOX_H */
