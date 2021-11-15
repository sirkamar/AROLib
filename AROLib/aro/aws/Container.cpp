#include <aro/core.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/aws/Window.hpp>
#include <aro/aws/Graphics.hpp>
#include <aro/aws/Container.hpp>
#include <aro/util/ArrayList.hpp>
#include <aro/aws/event/KeyEvent.hpp>

namespace aro {

namespace aws {

using namespace event;

const RArray<Component> Container::EMPTY_ARRAY = new Array<Component>(0);

Container::Container()
{
   cmp = new util::ArrayList<Component>();
   focusable = false;
   inSub = false;
   pos = 0;
}

Container::Container(RLayout layout)
{
   cmp = new util::ArrayList<Component>();
   focusable = false;
   manager = layout;
   inSub = false;
   pos = 0;
}

vint Container::getComponentCount()
{
   vint val = -1;
   
   sync_lock(getTreeLock())
   {
      val = cmp->size();
   }
   
   return val;
}

RDimension Container::getMaximumSize()
{
   if(max == nullref)
   {
      RDimension dim = (manager != nullref) ?
         manager->recommendMaxSize(thisref) :
         Component::getMaximumSize();
      
      max = dim;
   }
   
   return max;
}

RDimension Container::getMinimumSize()
{
   if(min == nullref)
   {
      RDimension dim = (manager != nullref) ?
         manager->recommendMinSize(thisref) :
         Component::getMinimumSize();
      
      min = dim;
   }
   
   return min;
}

RDimension Container::getPreferredSize()
{
   RDimension dim = prefer;
   
   if(prefer == nullref || !isValid())
   {
      sync_lock(getTreeLock())
      {
         prefer = (manager != nullref) ?
            manager->recommendPrefSize(thisref) :
            Component::getPreferredSize();
            
         dim = prefer;
      }
	  
   }
   
   if(dim == nullref)
      return dim;
   
   return new Dimension(dim);
}

RComponent Container::getComponent(vint index)
{
   RComponent tmp;
   
   sync_lock(getTreeLock())
   {
      if(index < 0 || index >= cmp->size())
         ex_throw new IndexException("no such component: ", index);
      
      tmp = cmp->get(index);
   }
   
   
   return tmp;
}

RArray<Component> Container::getComponents()
{
   RArray<Component> tmp;
   
   sync_lock(getTreeLock())
   {
      tmp = cmp->toArray();
   }
   
   
   return tmp;
}

void Container::add(RComponent comp)
{
   add(comp, -1);
}

void Container::add(RComponent comp, vint index)
{
   add(comp, "", index);
}

void Container::add(RComponent comp, RObject info)
{
   add(comp, info, -1);
}

void Container::add(RComponent comp, RObject info, vint index)
{
   sync_lock(getTreeLock())
   {
      if(index > cmp->size() || (index<0 && index != -1))
         ex_throw new ArgumentException("Illegal component position:" +
                                                String::valueOf(index));
      
      if(comp == nullref)
         ex_throw new NullException("Component cannot be null");
      
      if(type_of<Container>(comp))
      {
         for(RContainer cn = thisref; cn != nullref; cn = cn->parent)
         {
            if(cn == comp) // adding parent container not allowed
               ex_throw new ArgumentException("Cannot add parent component to child");
         }
         
         if(type_of<Window>(comp)) // Window is top-level parent
            ex_throw new ArgumentException("Cannot add Window to container");
      }
      
      if(comp->parent != nullref)
         comp->parent->remove(comp);
      
      if(index == -1)
         cmp->add(comp);
      else
         cmp->add(index, comp);
      
      comp->parent = thisref;
      
      if(valid)
         invalidate();
      
      if(manager != nullref)
         manager->addLayoutComponent(comp, info);
   }
   
}

void Container::remove(RComponent comp)
{
   if(comp == nullref)
      ex_throw new NullException("Component cannot be null");
   
   sync_lock(getTreeLock())
   {
      if(comp->parent == thisref)
      {
         vint index = cmp->indexOf(comp);
         
         if(index >= 0)
            remove(index);
      }
   }
}

void Container::setLayout(RLayout layout)
{
   manager = layout;
   
   if(valid)
      invalidate();
}

void Container::remove(vint index)
{
   sync_lock(getTreeLock())
   {
      if(index<0 || index>=cmp->size())
         ex_throw new IndexException("no such component: ", index);
      
      RComponent comp = cmp->get(index);
      
      if(manager != nullref)
         manager->removeLayoutComponent(comp);
      
      comp->parent = nullref;
      cmp->remove(comp);
      
      if(valid)
         invalidate();
   }
   
}

RLayout Container::getLayout()
{
   return manager;
}

RInsets Container::getInsets()
{
   return new Insets(0,0,0,0);
}

void Container::removeAll()
{
   sync_lock(getTreeLock())
   {
      while(!cmp->isEmpty())
      {
         RComponent comp = cmp->remove(cmp->size()-1);
         
         if(manager != nullref)
            manager->removeLayoutComponent(comp);
         
         comp->parent = nullref;
      }
      
      if(valid)
         invalidate();
   }
   
}

void Container::doLayout()
{
   if(manager != nullref)
      manager->layoutContainer(thisref);
}

//void Container::paint(RGraphics g)
//{
//   Component::paint(g);
//   
//   if(isShowing())
//   {
//      vint num = cmp->size();
//      for(vint i=0; i<num; i++)
//         cmp->get(i)->repaint();
//   }
//}

void Container::invalidate()
{
   if(valid)
      Component::invalidate();
}

void Container::validate()
{
   if(!valid && ignoreValidity)
   {
      sync_lock(getTreeLock())
      {
         validateTree();
         
         if(parent == nullref || parent->valid)
            repaint();
      }
	  
   }
}

void Container::validateTree()
{
   if(!valid || ignoreValidity)
   {
      if(!valid)
         doLayout();
      
      for(vint i=0; i<cmp->size(); i++)
      {
         RComponent comp = cmp->get(i);
         
         if(type_of<Container>(comp) && !type_of<Window>(comp) && (!comp->valid || ignoreValidity))
            type_cast<Container>(comp)->validateTree();
         else
            comp->validate();
      }
   }
   
   Component::validate();
}

void Container::validateUnconditionally()
{
   sync_lock(getTreeLock())
   {
      ignoreValidity = true;

      validate();

      ignoreValidity = false;
   }
}

vbool Container::isAncestorOf(RComponent comp)
{
   RContainer p;
   
   if(comp == nullref || (p = comp->getParent()) == nullref)
      return false;
   
   while(p != nullref)
   {
      if(p == thisref)
         return true;
      
      p = p->getParent();
   }
   
   return false;
}

RComponent Container::getPrevious()
{
   if(pos >= cmp->size()) pos = cmp->size();
   
   while(pos > 0)
   {
      RComponent comp = cmp->get(pos-1);
      
      if(comp->visible)
      {
         if(comp->focusable)
         {
            inSub = false;
            return cur = cmp->get(--pos);
         }
         
         if(type_of<Container>(comp))
         {
            if(inSub)
               cur = type_cast<Container>(comp)->getPrevious();
            else
            {
               inSub = true;
               cur = type_cast<Container>(comp)->getLast();
            }
            
            if(cur != nullref)
               return cur;
         }
      }
      
      inSub = false;
      --pos;
   }
   
   return cur = nullref;
}

RComponent Container::getCurrent()
{
   return cur;
}

RComponent Container::getNext()
{
   if(pos < 0) pos = -1;
   
   while(pos < cmp->size()-1)
   {
      RComponent comp = cmp->get(pos+1);
      
      if(comp->visible)
      {
         if(comp->focusable)
         {
            inSub = false;
            return cur = cmp->get(++pos);
         }
         
         if(type_of<Container>(comp))
         {
            if(inSub)
               cur = type_cast<Container>(comp)->getNext();
            else
            {
               inSub = true;
               cur = type_cast<Container>(comp)->getFirst();
            }
            
            if(cur != nullref)
               return cur;
         }
      }
      
      inSub = false;
      ++pos;
   }
   
   return cur = nullref;
}

RComponent Container::getFirst()
{
   pos = -1; inSub = false;
   
   while(pos < cmp->size()-1)
   {
      RComponent comp = cmp->get(pos+1);
      
      if(comp->visible)
      {
         if(comp->focusable)
         {
            inSub = false;
            return cur = cmp->get(++pos);
         }
         
         if(type_of<Container>(comp))
         {
            inSub = true;
            cur = type_cast<Container>(comp)->getFirst();
            
            if(cur != nullref)
               return cur;
         }
      }
      
      inSub = false;
      ++pos;
   }
   
   return cur = nullref;
}

RComponent Container::getLast()
{
   pos = cmp->size(); inSub = false;
   
   while(pos > 0)
   {
      RComponent comp = cmp->get(pos-1);
      
      if(comp->visible)
      {
         if(comp->focusable)
         {
            inSub = false;
            return cur = cmp->get(--pos);
         }
         
         if(type_of<Container>(comp))
         {
            inSub = true;
            cur = type_cast<Container>(comp)->getLast();
            
            if(cur != nullref)
               return cur;
         }
      }
      
      inSub = false;
      --pos;
   }
   
   return cur = nullref;
}

void Container::preProcessKeyEvent(RKeyEvent e)
{
   RContainer parent = thisref->parent;

   if(parent != nullref)
      parent->preProcessKeyEvent(e);
}

void Container::postProcessKeyEvent(RKeyEvent e)
{
   RContainer parent = thisref->parent;
   
   if(parent != nullref)
      parent->postProcessKeyEvent(e);
}

void Container::paint(RGraphics g)
{
   if(isShowing())
   {
      RArray<Component> comps = getComponents();

      for(int n = 0; n < comps->length; n++)
      {
         RComponent c = comps[n];

         if(c != nullref && c->isVisible())
         {
            g->initBounds(c);
            
            c->paint(g);
         }
      }
   }
}

void Container::update(RGraphics g)
{
   if(isShowing())
   {
      g->clearRectangle(0, 0, width, height);
      //g->clear();
      
      paint(g);
   }
}

void Container::paintComponents(RGraphics g)
{
   if(isShowing())
   {
      RArray<Component> comps = getComponents();

      for(int n = 0; n < comps->length; n++)
      {
         RComponent c = comps[n];

         if(c != nullref && c->isVisible())
            c->paintAll(g);
      }
   }
}

} /* namespace aws */

} /* namespace aro */
