#include <aro/core.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/cui/event/TextEvent.hpp>
#include <aro/cui/CSTextComponent.hpp>

namespace aro {

namespace cui {

using namespace event;

CSTextComponent::CSTextComponent(RString str)
{
   text = new StringBuffer((str != nullref) ? str : "");
   setFocusable(true);
   editable = true;
}

void CSTextComponent::selectAll()
{
   sync_lock(thisref)
   {
      selectionStart = 0;
      selectionEnd = getText()->length();

	  //see comments under CSTextComponent::select(start,end)
   }
}

RString CSTextComponent::getText()
{
   return text->toString();
}

vbool CSTextComponent::isEditable()
{
   return editable;
}

vint CSTextComponent::getSelectionEnd()
{
   return selectionEnd;
}

vint CSTextComponent::getSelectionStart()
{
   return selectionStart;
}

void CSTextComponent::setEditable(vbool b)
{
   if(editable == b)
      return;
   
   RBool old = Bool::valueOf(editable);
   
   editable = b;
   
   firePropertyChanged("editable", old, Bool::valueOf(b));
}

void CSTextComponent::setText(RString str)
{
   str = (str != nullref) ? str : "";
   
   RString old = text->toString();
   
   vint length = str->length();

   text->insert(0, str);

   text->setLength(length);
   
   fireTextChanged();
   
   if(str == nullref || old == nullref || !str->equals(old))
   {
      revalidate();
      repaint();
   }
}

void CSTextComponent::setSelectionEnd(vint end)
{
   select(getSelectionStart(), end);
}

void CSTextComponent::select(vint start, vint end)
{
   sync_lock(thisref)
   {
      if(start < 0)
         start = 0;

      if(start > text->length())
         start = text->length();

      if(end > text->length())
         end = text->length();

      if(end < start)
         end = start;
      
      selectionStart = start;
      selectionEnd = end;
   }

   //option 1
   //implement a selection change notification
   //so that it can be refelected on screen
   //for components able to do so.

   //option 2
   //derived classes can override this function but
   //still call CSTextComponent::select(start,end) to
   //validate and normalize selection start and end
}

void CSTextComponent::setSelectionStart(vint start)
{
   select(start, getSelectionEnd());
}

void CSTextComponent::addTextListener(RTextListener l)
{
   listeners->add<TextListener>(l);
}

void CSTextComponent::removeTextListener(RTextListener l)
{
   listeners->remove<TextListener>(l);
}

RArray<TextListener> CSTextComponent::getTextListeners()
{
   return listeners->getListeners<TextListener>();
}

void CSTextComponent::processTextEvent(RTextEvent e)
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<TextListener>(arr[n]))
      {
         RTextListener rtl = type_cast<TextListener>(arr[n]);
         
         rtl->textChanged(e);
      }
   }
}

void CSTextComponent::processKeyEvent(aws::event::RKeyEvent e)
{
   
}

void CSTextComponent::processEvent(aws::RAWSEvent e)
{
	if(type_of<TextEvent>(e))
		processTextEvent(type_cast<TextEvent>(e));
	else
		Component::processEvent(e);
}

void CSTextComponent::fireTextChanged()
{
   RArray<util::Listener> arr = listeners->getListeners();
   
   RTextEvent e = new TextEvent(thisref);
   
   for(vint n=0; n<arr->length; n++)
   {
      if(type_of<TextListener>(arr[n]))
      {
         RTextListener rtl = type_cast<TextListener>(arr[n]);
         
         rtl->textChanged(e);
      }
   }
}

void CSTextComponent::paintComponent(aws::RGraphics g)
{
   CSComponent::paintComponent(g);
}

} /* namespace aws */

} /* namespace aro */
