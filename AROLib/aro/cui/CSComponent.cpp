#include <aro/aws/Insets.h>
#include <aro/aws/Graphics.h>
#include <aro/cui/CSComponent.h>
#include <aro/aws/event/KeyEvent.h>

namespace aro {

using namespace aws;

namespace cui {

CSComponent::CSComponent()
{
   
}

RBorder CSComponent::getBorder()
{
   return border;
}

RInsets CSComponent::getInsets()
{
   if(border != nullref)
      return border->getInsets();
   
   return Container::getInsets();
}

void CSComponent::setEnabled(vbool b)
{
   vbool oldEnabled = isEnabled();

   Container::setEnabled(b);

   firePropertyChanged("enabled", new Bool(oldEnabled), new Bool(b));

   if(b != oldEnabled)
      repaint();
}

void CSComponent::setVisible(vbool b)
{
   if(b != isVisible())
   {
      Container::setVisible(b);

      if(b)
      {
         RContainer parent = getParent();
         if(parent != nullref)
         {
            RRectangle r = getBounds();
            parent->repaint(r->x, r->y, r->width, r->height);
         }
         revalidate();
      }
   }
}

void CSComponent::setBorder(RBorder b)
{
   RBorder oldBorder = border;

   border = b;

   firePropertyChanged("border", oldBorder, b);

   if(b != oldBorder)
   {
      if(b != nullref || oldBorder != nullref ||
         !b->getInsets()->equals(oldBorder->getInsets()))
      {
         revalidate();
      }

      repaint();
   }
}

RDimension CSComponent::getMaximumSize()
{
   if(isMaximumSizeSet())
      return Container::getMaximumSize();
   
   //TODO: calculate maximum size based on parent and insets
   return Container::getMaximumSize(); //then replace this line
}

RDimension CSComponent::getMinimumSize()
{
   if(isMinimumSizeSet())
      return Container::getMinimumSize();
   
   RDimension dim = getSize();
   RInsets ins = getInsets();

   return new Dimension(dim->width+ins->left+ins->right, dim->height+ins->top+ins->bottom);
}

RDimension CSComponent::getPreferredSize()
{
   if(isPreferredSizeSet())
      return Container::getPreferredSize();
   
   return getMinimumSize();
}

void CSComponent::paint(RGraphics g)
{
   if((getWidth() <= 0) || (getHeight() <= 0)) {
      return;
   }
   
   g->initBounds(thisref);

   paintComponent(g);
   paintBorder(g);

   paintChildren(g);
}

void CSComponent::update(RGraphics g)
{
   paint(g);
}

void CSComponent::paintBorder(RGraphics g)
{
   RBorder border = getBorder();
   
   if(border != nullref)
      border->paintBorder(thisref, g);// , 0, 0, getWidth(), getHeight());
}

void CSComponent::paintChildren(RGraphics g)
{
   sync_lock(getTreeLock())
   {
      int i = getComponentCount() - 1;
      if(i < 0) {
         return;
      }
      
      for(; i >= 0; i--) {
         RComponent comp = getComponent(i);
         if(comp == nullref) {
            continue;
         }

         if(comp->isVisible())
         {
            comp->paint(g);
         }
      }
   }
}

void CSComponent::paintComponent(RGraphics g)
{
   
}



void CSComponent::processKeyEvent(event::RKeyEvent e)
{
   Container::processKeyEvent(e);

   if(!e->isConsumed())
      processComponentKeyEvent(e);

   if(e->isConsumed())
      return;
   
   //if(processKeyBindings(e, e->getEventID() == KeyEvent::KEY_PRESSED))
   //   e->consume();
}

void CSComponent::processComponentKeyEvent(event::RKeyEvent e)
{
   
}

} /* namespace cui */

} /* namespace aro */
