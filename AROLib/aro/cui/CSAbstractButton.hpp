#ifndef CUI_ABSTRACTBUTTON_H
#define CUI_ABSTRACTBUTTON_H

#include <aro/aws/Selectable.hpp>
#include <aro/cui/CSComponent.hpp>
#include <aro/cui/CSButtonGroup.hpp>
#include <aro/cui/CUIConstants.hpp>
#include <aro/cui/event/ChangeEvent.hpp>
#include <aro/aws/event/ItemListener.hpp>
#include <aro/cui/event/ChangeListener.hpp>
#include <aro/aws/event/ActionListener.hpp>

namespace aro {

namespace cui {

class CSAbstractButton;
typedef Ref<CSAbstractButton> RCSAbstractButton;

class CSAbstractButton extends public CSComponent implements public aws::Selectable, public CUIConstants
{
   public:
      static const vint ENABLED;
      static const vint PRESSED;
      static const vint SELECTED;

      CSAbstractButton();

      virtual void doClick();
      virtual void doClick(vint pressTime);

      virtual vbool isEnabled();
      virtual vbool isPressed();
      virtual vbool isSelected();

      virtual void setEnabled(vbool b);
      virtual void setPressed(vbool b);
      virtual void setSelected(vbool b);

      virtual vint getMnemonic();
      virtual void setMnemonic(vint key);
      
      virtual RString getText();
      virtual void setText(RString text);

      virtual RString getActionCommand();
      virtual void setActionCommand(RString str);

      virtual RCSButtonGroup getGroup();
      virtual void setGroup(RCSButtonGroup group);
      
      virtual RArray<Object> getSelectedObjects();
      
      virtual vint getDisplayedMnemonicIndex();
      virtual void setDisplayedMnemonicIndex(vint index);

      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getPreferredSize();

      virtual vint getVerticalTextPosition();
      virtual vint getHorizontalTextPosition();

      virtual void setVerticalTextPosition(vint pos);
      virtual void setHorizontalTextPosition(vint pos);

      virtual void addItemListener(aws::event::RItemListener l);
      virtual void removeItemListener(aws::event::RItemListener l);
      virtual RArray<aws::event::ItemListener> getItemListeners();
      
      virtual void addChangeListener(event::RChangeListener l);
      virtual void removeChangeListener(event::RChangeListener l);
      virtual RArray<event::ChangeListener> getChangeListeners();

      virtual void addActionListener(aws::event::RActionListener l);
      virtual void removeActionListener(aws::event::RActionListener l);
      virtual RArray<aws::event::ActionListener> getActionListeners();
   
   protected:
      RCSButtonGroup group;
      vint mnemonic, stateMask;
      RString text, actionCommand;
      event::RChangeEvent changeEvent;

      void fireStateChanged();
      void fireItemStateChanged(aws::event::RItemEvent e);
      void fireActionOccurred(aws::event::RActionEvent e);

      //virtual void paint(RGraphics g);
      virtual void processKeyEvent(aws::event::RKeyEvent e);

   private:
      vint mnemonicIndex;
      vint hTextPos, vTextPos;
      
      void updateDisplayedMnemonicIndex(RString text, vint mnemonic);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_ABSTRACTBUTTON_H */
