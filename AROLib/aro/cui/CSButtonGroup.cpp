#include <aro/core.hpp>
#include <aro/cui/CSButtonGroup.hpp>
#include <aro/cui/CSAbstractButton.hpp>

namespace aro {

namespace cui {

CSButtonGroup::CSButtonGroup()
{
   buttons = new util::Vector<CSAbstractButton>();
}

vint CSButtonGroup::getButtonCount()
{
   if(buttons == nullref)
      return 0;

   return buttons->size();
}

void CSButtonGroup::clearSelection()
{
   if(selection != nullref)
   {
      RCSAbstractButton oldSelection = selection;
      selection = nullref;
      oldSelection->setSelected(false);
   }
}

void CSButtonGroup::add(RCSAbstractButton b)
{
   if(b == nullref)
      return;

   buttons->addElement(b);

   if(b->isSelected())
   {
      if(selection == nullref)
         selection = b;
      else
         b->setSelected(false);
   }

   b->setGroup(thisref);
}

void CSButtonGroup::remove(RCSAbstractButton b)
{
   if(b == nullref)
      return;

   buttons->removeElement(b);

   if(b == selection)
      selection = nullref;

   b->setGroup(nullref);
}

RCSAbstractButton CSButtonGroup::getSelection()
{
   return selection;
}

vbool CSButtonGroup::isSelected(RCSAbstractButton b)
{
   return (b == selection);
}

util::RIterator<CSAbstractButton> CSButtonGroup::getButtons()
{
   return buttons->elements();
}

void CSButtonGroup::setSelected(RCSAbstractButton b, vbool s)
{
   if(s && b != nullref && b != selection)
   {
      if(selection != nullref)
         selection->setSelected(false);
      
      b->setSelected(true);
      
      selection = b;
   }
}

} /* namespace cui */

} /* namespace aro */
