#ifndef AWS_CSTEXTCOMPONENT_H
#define AWS_CSTEXTCOMPONENT_H

#include <aro/cui/CSComponent.h>
#include <aro/cui/event/TextListener.h>

namespace aro {

namespace cui {

class CSTextComponent;
typedef Ref<CSTextComponent> RTextComponent;

class CSTextComponent : public CSComponent
{
   public:
      CSTextComponent(RString text);
      
      virtual void selectAll();
      virtual RString getText();
      virtual vbool isEditable();
	   virtual vint getSelectionEnd();
      virtual vint getSelectionStart();
      virtual void setEditable(vbool b);
      virtual void setText(RString text);
      virtual void setSelectionEnd(vint end);
      virtual void select(vint start, vint end);
      virtual void setSelectionStart(vint start);
      virtual void addTextListener(event::RTextListener l);
      virtual void removeTextListener(event::RTextListener l);
      virtual RArray<event::TextListener> getTextListeners();
   
   protected:
      RStringBuffer text;
      
      virtual void fireTextChanged();
      virtual void processEvent(aws::RAWSEvent e);
      virtual void paintComponent(aws::RGraphics g) = 0;
      virtual void processTextEvent(event::RTextEvent e);
      virtual void processKeyEvent(aws::event::RKeyEvent e);
   
   private:
      vbool editable;
      vint selectionStart, selectionEnd;
};

} /* namespace cui */

} /* namespace aro */

#endif /* AWS_CSTEXTCOMPONENT_H */
