#include <aro/core.h>
#include <aro/aws/Point.h>
#include <aro/aws/Insets.h>
#include <aro/aws/DeckLayout.h>

namespace aro {

namespace aws {

DeckLayout::Card::Card(RString nm, RComponent cmp)
{
   name = nm;
   comp = cmp;
}

DeckLayout::DeckLayout()
{
   hgap = vgap = 0;
   currentCard = 0;
   vector = new util::Vector<Card>();
}

DeckLayout::DeckLayout(vint hg, vint vg)
{
   hgap = hg;
   vgap = vg;
   currentCard = 0;
   vector = new util::Vector<Card>();
}

RString DeckLayout::toString()
{
   return getType() + " [hgap:" + String::valueOf(hgap) +
          " vgap:" + String::valueOf(vgap) + "]";
}

void DeckLayout::layoutContainer(RContainer target)
{
   RDimension dim = target->getSize();
   RInsets insets = target->getInsets();
   vint ncomps = target->getComponentCount();
   RComponent comp = nullref; vbool currentFound = false;
   
   for(vint i=0; i<ncomps; i++)
   {
      comp = target->getComponent(i);
      comp->setLocation(hgap + insets->left, vgap + insets->top);
      comp->setSize(dim->width - (hgap*2 + insets->left + insets->right),
                    dim->height - (vgap*2 + insets->top + insets->bottom));
      
      if(comp->isVisible())
         currentFound = true;
      
      if(!currentFound && ncomps > 0)
         target->getComponent(0)->setVisible(true);
   }
}

void DeckLayout::removeLayoutComponent(RComponent comp)
{
   for(vint i=0; i<vector->size(); i++)
   {
      if(vector->elementAt(i)->comp == comp)
      {
         if(comp->isVisible() && comp->getParent() != nullref)
            next(comp->getParent());
         
         vector->removeElementAt(i);
         
         if(currentCard > i)
            currentCard--;
         
         break;
      }
   }
}

RDimension DeckLayout::recommendMaxSize(RContainer target)
{
   return target->Component::getMaximumSize();
}

RDimension DeckLayout::recommendMinSize(RContainer target)
{
   RInsets insets = target->getInsets();
   vint ncomps = target->getComponentCount();
   
   vint w=0, h=0;
   
   for(vint i=0; i<ncomps; i++)
   {
      RComponent comp = target->getComponent(i);
      RDimension d = comp->getMinimumSize();
      
      if(d->width > w)
         w = d->width;
      
      if(d->height > h)
         h = d->height;
   }
   
   return new Dimension(insets->left + insets->right + w + hgap*2,
                        insets->top + insets->bottom + h + vgap*2);
}

RDimension DeckLayout::recommendPrefSize(RContainer target)
{
   RInsets insets = target->getInsets();
   vint ncomps = target->getComponentCount();
   
   vint w=0, h=0;
   
   for(vint i=0; i<ncomps; i++)
   {
      RComponent comp = target->getComponent(i);
      RDimension d = comp->getPreferredSize();
      
      if(d->width > w)
         w = d->width;
      
      if(d->height > h)
         h = d->height;
   }
   
   return new Dimension(insets->left + insets->right + w + hgap*2,
                        insets->top + insets->bottom + h + vgap*2);
}

void DeckLayout::addLayoutComponent(RComponent comp, RObject info)
{
   if(!type_of<String>(info))
      ex_throw new ArgumentException("CardLayout constraint must be a String");
   
   RString name = type_cast<String>(info);
   
   if(vector->isEmpty())
      comp->setVisible(false);
   
   for(vint i=0; i<vector->size(); i++)
   {
      if(vector->elementAt(i)->name->equals(name))
      {
         vector->elementAt(i)->comp = comp;
         return;
      }
   }
   
   vector->addElement(new Card(name, comp));
}

void DeckLayout::show(RContainer target, RString name)
{
   checkLayout(target);
   
   RComponent next = nullref;
   vint ncomps = vector->size();
   
   for(vint n=0; n<ncomps; n++)
   {
      RCard card = vector->elementAt(n);
      
      if(card->name->equals(name))
      {
         next = card->comp;
         
         currentCard = n;
         
         break;
      }
   }
   
   if((next != nullref) && !next->isVisible())
   {
      ncomps = target->getComponentCount();
      
      for(vint n=0; n<ncomps; n++)
      {
         RComponent comp = target->getComponent(n);
         
         if(comp->isVisible())
         {
            comp->setVisible(false);
            
            break;
         }
      }
      
      next->setVisible(true);
      
      target->validate();
   }
}

void DeckLayout::previous(RContainer target)
{
   checkLayout(target);
   
   vint ncomps = target->getComponentCount();
   
   for(vint n=0; n<ncomps; n++)
   {
      RComponent comp = target->getComponent(n);
      
      if(comp->isVisible())
      {
         comp->setVisible(false);
         
         currentCard = ((n>0) ? n-1 : ncomps-1);
         
         comp = target->getComponent(currentCard);
         
         comp->setVisible(true);
         
         target->validate();
         
         return;
      }
   }
   
   showDefaultComponent(target);
}

void DeckLayout::first(RContainer target)
{
   checkLayout(target);
   
   vint ncomps = target->getComponentCount();
   
   for(vint n=0; n<ncomps; n++)
   {
      RComponent comp = target->getComponent(n);
      
      if(comp->isVisible())
      {
         comp->setVisible(false);
         
         break;
      }
   }
   
   if(ncomps > 0)
   {
      currentCard = 0;
      
      target->getComponent(0)->setVisible(true);
      
      target->validate();
   }
}

void DeckLayout::next(RContainer target)
{
   checkLayout(target);
   
   vint ncomps = target->getComponentCount();
   
   for(vint n=0; n<ncomps; n++)
   {
      RComponent comp = target->getComponent(n);
      
      if(comp->isVisible())
      {
         comp->setVisible(false);
         
         currentCard = (n + 1) % ncomps;
         
         comp = target->getComponent(currentCard);
         
         comp->setVisible(true);
         
         target->validate();
         
         return;
      }
   }
   
   showDefaultComponent(target);
}

void DeckLayout::last(RContainer target)
{
   checkLayout(target);
   
   vint ncomps = target->getComponentCount();
   
   for(vint n=0; n<ncomps; n++)
   {
      RComponent comp = target->getComponent(n);
      
      if(comp->isVisible())
      {
         comp->setVisible(false);
         
         break;
      }
   }
   
   if(ncomps > 0)
   {
      currentCard = ncomps - 1;
      
      target->getComponent(currentCard)->setVisible(true);
      
      target->validate();
   }
}

void DeckLayout::checkLayout(RContainer target)
{
   if(target->getLayout() != thisref)
      ex_throw new ArgumentException("Wrong target for DeckLayout");
}

void DeckLayout::showDefaultComponent(RContainer target)
{
   if(target->getComponentCount() > 0)
   {
      currentCard = 0;
      
      target->getComponent(0)->setVisible(true);
      
      target->validate();
   }
}

} /* namespace aws */

} /* namespace aro */
