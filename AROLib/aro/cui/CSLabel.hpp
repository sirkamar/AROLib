#ifndef CUI_CSLABEL_H
#define CUI_CSLABEL_H

#include <aro/cui/CSComponent.hpp>
#include <aro/cui/CUIConstants.hpp>

namespace aro {

namespace cui {

class CSLabel;
typedef Ref<CSLabel> RCSLabel;

class CSLabel : public CSComponent, public CUIConstants
{
   public:
      CSLabel();
      CSLabel(RString text);

      virtual RString getText();
      virtual void setText(RString text);
      virtual int getDisplayedMnemonic();
      virtual aws::RComponent getLabelFor();
      virtual int getVerticalTextPosition();
      virtual int getHorizontalTextPosition();
      virtual int getDisplayedMnemonicIndex();
      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getPreferredSize();
      virtual void setDisplayedMnemonic(int key);
      virtual void setLabelFor(aws::RComponent c);
      virtual void setVerticalTextPosition(int pos);
      virtual void setHorizontalTextPosition(int pos);
      virtual void setDisplayedMnemonicIndex(int index);

   protected:
      aws::RComponent labelFor;

      virtual void paintComponent(aws::RGraphics g);

   private:
      RString text;
      int hTextPos, vTextPos;
      int mnemonic, mnemonicIndex;
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSLABEL_H */
