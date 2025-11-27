#ifndef CUI_CSTEXTBOX_H
#define CUI_CSTEXTBOX_H

#include <aro/cui/CUIConstants.hpp>
#include <aro/cui/CSTextComponent.hpp>
#include <aro/aws/event/ActionListener.hpp>

namespace aro {

namespace cui {

class CSTextBox;
typedef Ref<CSTextBox> RCSTextBox;

class CSTextBox extends public CSTextComponent implements public CUIConstants
{
   public:
      CSTextBox();
      CSTextBox(int cols);
      CSTextBox(RString text);
      CSTextBox(RString text, int cols);
      
      virtual int getColumns();
      virtual char getEchoChar();
      virtual bool isEchoCharSet();
      virtual void setEchoChar(char c);
      virtual void setColumns(int cols);
      //virtual void handleInput(int key);
      virtual int getVerticalTextPosition();
      virtual int getHorizontalTextPosition();
      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getPreferredSize();
      virtual void setVerticalTextPosition(int pos);
      virtual void setHorizontalTextPosition(int pos);
      virtual void addActionListener(aws::event::RActionListener l);
      virtual void removeActionListener(aws::event::RActionListener l);
   
   protected:
      char echoChar;
      virtual RString getEchoText();
      virtual void fireActionOccurred();
      virtual void paintComponent(aws::RGraphics g);
      virtual void processComponentKeyEvent(aws::event::RKeyEvent e);
   
   private:
      bool isMod;
      int columns;
      int vTextPos, hTextPos;
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSTEXTBOX_H */
