#ifndef CUI_CSBUTTONGROUP_H
#define CUI_CSBUTTONGROUP_H

#include <aro/core/String.h>
#include <aro/util/Vector.h>

namespace aro {

namespace cui {

class CSButtonGroup;
class CSAbstractButton;
typedef Ref<CSButtonGroup> RCSButtonGroup;
typedef Ref<CSAbstractButton> RCSAbstractButton;

class CSButtonGroup : public Object
{
   public:
      CSButtonGroup();
      
      virtual vint getButtonCount();
      virtual void clearSelection();
      virtual void add(RCSAbstractButton b);
      virtual void remove(RCSAbstractButton b);
      virtual RCSAbstractButton getSelection();
      virtual vbool isSelected(RCSAbstractButton b);
      virtual void setSelected(RCSAbstractButton b, vbool s);
      virtual util::RIterator<CSAbstractButton> getButtons();
   
   protected:
      RCSAbstractButton selection;
      util::RVector<CSAbstractButton> buttons;
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSBUTTONGROUP_H */
