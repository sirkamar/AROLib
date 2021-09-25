#include <aro/core.h>
#include <aro/aws/Window.h>
#include <aro/core/ArgumentException.h>
#include <aro/aws/DefaultFocusPolicy.h>

namespace aro {

namespace aws {

const DefaultFocusPolicy::RMutableBool DefaultFocusPolicy::found =
                                    new DefaultFocusPolicy::MutableBool();

vbool DefaultFocusPolicy::accept(RComponent comp)
{
   if(!(comp->isVisible() && comp->isFocusable() && comp->isEnabled()))
      return false;
   
   for(RContainer test=comp->getParent(); test != nullref; test=test->getParent())
   {
      if(!test->isEnabled())
         return false;
      
      if(type_of<Window>(test))
         break;
   }
   
   return true;
}

RComponent DefaultFocusPolicy::getLast(RContainer parent)
{
   if(parent == nullref)
      ex_throw new ArgumentException("parent cannot be null");
   
   RComponent retval;
   
   sync_lock(parent->getTreeLock())
   {
      if(parent->isVisible())
      {
         vint comps = parent->getComponentCount();
         
         for(vint n=comps-1; n>=0; n--)
         {
            RComponent c = parent->getComponent(n);
            
            if(type_of<Container>(c))
            {
               retval = getLast(type_cast<Container>(c));
               
               if(retval != nullref)
                  break;
            }
            else
            {
               if(accept(c))
               {
                  retval = c;
                  break;
               }
            }
         }
         
         if(retval == nullref && accept(parent))
            retval = parent;
      }
   }
   
   return retval;
}

RComponent DefaultFocusPolicy::getFirst(RContainer parent)
{
   if(parent == nullref)
      ex_throw new ArgumentException("parent cannot be null");
   
   RComponent retval;
   
   sync_lock(parent->getTreeLock())
   {
      if(parent->isVisible())
      {
         if(accept(parent))
            retval = parent;
         
         if(retval != nullref)
         {
            vint comps = parent->getComponentCount();
            
            for(vint n=0; n<comps; n++)
            {
               RComponent c = parent->getComponent(n);
               
               if(type_of<Container>(c))
               {
                  retval = getFirst(type_cast<Container>(c));
                  
                  if(retval != nullref)
                     break;
               }
               else
               {
                  if(accept(c))
                  {
                     retval = c;
                     break;
                  }
               }
            }  
         }
      }
   }
   
   return retval;
}

RComponent DefaultFocusPolicy::getDefault(RContainer parent)
{
   return getFirst(parent);
}

RComponent DefaultFocusPolicy::getNext(RContainer parent,
                                                 RComponent comp)
{
   if(parent == nullref || comp == nullref)
      ex_throw new ArgumentException("parent and comp cannot be null");
   
   if(!parent->isAncestorOf(comp))
      ex_throw new ArgumentException("parent is not an ancestor of comp");
   
   RComponent retval;
   
   sync_lock(parent->getTreeLock())
   {
      found->value = false;
      
      retval = getNext(parent, comp, found);
      
      if(retval == nullref && found->value)
         retval = getFirst(parent);
   }
   
   return retval;
}

RComponent DefaultFocusPolicy::getPrevious(RContainer parent,
                                                       RComponent comp)
{
   if(parent == nullref || comp == nullref)
      ex_throw new ArgumentException("parent and comp cannot be null");
   
   if(!parent->isAncestorOf(comp))
      ex_throw new ArgumentException("parent is not an ancestor of comp");
   
   RComponent retval;
   
   sync_lock(parent->getTreeLock())
   {
      found->value = false;
      
      retval = getPrevious(parent, comp, found);
      
      if(retval == nullref && found->value)
         retval = getLast(parent);
   }
   
   return retval;
}

RComponent DefaultFocusPolicy::getNext(RContainer parent,
                RComponent comp, DefaultFocusPolicy::RMutableBool fnd)
{
   if(!parent->isVisible())
      return nullref;
   
   if(found->value)
   {
      if(accept(parent))
         return parent;
   }
   else if(parent == comp)
      found->value = true;
   
   vint comps = parent->getComponentCount();
   
   for(vint n=0; n<comps; n++)
   {
      RComponent c = parent->getComponent(n);
      
      if(type_of<Container>(c))
      {
         RComponent retval = getNext(type_cast<Container>(c), comp, found);
         
         if(retval != nullref)
            return retval;
      }
      else if(found->value)
      {
         if(accept(c))
            return c;
      }
      else if(c == comp)
         found->value = true;
   }
   
   return nullref;
}

RComponent DefaultFocusPolicy::getPrevious(RContainer parent,
                RComponent comp, DefaultFocusPolicy::RMutableBool fnd)
{
   if(!parent->isVisible())
      return nullref;
   
   vint comps = parent->getComponentCount();
   
   for(vint n=comps-1; n>=0; n--)
   {
      RComponent c = parent->getComponent(n);
      
      if(type_of<Container>(c))
      {
         RComponent retval = getPrevious(type_cast<Container>(c), comp, found);
         
         if(retval != nullref)
            return retval;
      }
      else if(found->value)
      {
         if(accept(c))
            return c;
      }
   }
   
   if(found->value)
   {
      if(accept(parent))
         return parent;
   }
   else if(parent == comp)
      found->value = true;
   
   return nullref;
}

} /* namespace aws */

} /* namespace aro */
