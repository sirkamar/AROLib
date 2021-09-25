#include <aro/core.h>
#include <aro/aws/Insets.h>
#include <aro/cui/CSList.h>
#include <aro/cui/border/LineBorder.h>
#include <aro/aws/event/SelectionEvent.h>

namespace aro {

namespace cui {

using namespace aws;
using namespace aws::event;

CSList::CSList()
{
   count = 0;
   focused = -1;
   visCount = 4;
   selected = -1;
   setFocusable(true);
   visFirst = visLast = 0;
   border = new LineBorder();
   items = new Array<Object>(4);
}

CSList::CSList(RArray<Object> data)
{
   count = 0;
   focused = -1;
   visCount = 4;
   selected = -1;
   setFocusable(true);
   visFirst = visLast = 0;
   border = new LineBorder();
   items = new Array<Object>(data->length+4);
   
   for(int i=0; i<data->length; i++)
      addItem(data[i], i);
}

void CSList::addItem(RObject item)
{
   addItem(item, count);
}

void CSList::addItem(RObject item, int index)
{
   if(item == nullref)
      ex_throw new NullException("null not allowed in CSList");
   
   if(index<0 || index>count)
      ex_throw new IndexException("Invalid item index: ", index);
   
   if(items->length == count)
   {
      RArray<Object> temp = items;
      items = new Array<Object>(count*2+1);
      items->copy(0, temp, 0, count); temp = nullref;
   }
   
   if(index == count)
      items[count++] = item;
   else
   {
      items->copy(index+1, items, index, count-index);
      items[index] = item;
      count++;
   }
   
   if(isShowing())
      repaint();
}

void CSList::handleInput(int key)
{
   switch(key)
   {
      case 13: //RETURN
      case 32: //SPACE
         if(focused >= 0 && focused < count)
         {
            selected = focused;
            fireValueChangedEvent();
            repaint();
         }
         break;
      
      // move focus up
      case 72: //CURSOR_UP
         if(focused > 0)
         {
            focused--;
            scrollToFocused();
         }
         break;
      
      // move focus down
      case 80: //CURSOR_DOWN
         if(focused < count-1)
         {
            focused++;
            scrollToFocused();
         }
         break;
      
      // do nothing
      default:
         break;
   }
}

void CSList::setSelectedIndex(int index)
{
   if(index < -1 || index >= count)
      ex_throw new IndexException("Invalid item index: ", index);
   
   if(selected == index)
      return;
   
   focused = selected = index;
   
   scrollToFocused();
   fireValueChangedEvent();
}

void CSList::removeItem(RObject item)
{
   for(int i=0; i<count; i++)
   {
      if(items[i] == item)
      {
         removeItem(i);
         return;
      }
   }
}

RObject CSList::removeItem(int index)
{
   if(index<0 || index>=count)
      ex_throw new IndexException("Invalid item index: ", index);
   
   RObject item = items[index];
   
   count--;
   if(selected >= count)
      selected = count-1;
   
   if(index < count-1)
      items->copy(index, items, index+1, count-index-1);
   
   if(isShowing())
      repaint();
   
   return item;
}

RDimension CSList::getMinimumSize()
{
   RInsets ins = getInsets();
   
   return new Dimension
   (
      12+(ins->left+ins->right),
      3+(ins->top+ins->bottom)
   );
}

RDimension CSList::getPreferredSize()
{
   RInsets ins = getInsets();
   int maxSize = getWidestElementSize();
   
   return new Dimension
   (
      maxSize+(ins->left+ins->right),
      visCount*3+(ins->top+ins->bottom)
   );
}

void CSList::setVisibleRowCount(int rows)
{
   if(visCount == rows)
      return;
   
   if(rows < 1) rows = 4;
   
   RInt old = Int::valueOf(visCount);
   
   visCount = rows > 10 ? 10 : rows;
   
   firePropertyChanged("visibleRowCount", old, Int::valueOf(visCount));
   
   if(visCount > count) // unoccupied rows will exist
   {
      visFirst = 0;
      visLast = count-1;
   }
   else
   {
      if(visFirst+visCount < count)
         visLast = visFirst+visCount; // extend all downwards
      else
      {
         visLast = count-1; // extend down as much as possible
         visFirst = visLast-(visCount-1); // extend extra upwards
      }
   }
   
   scrollToFocused();
   
   if(isShowing())
      revalidate();
}

void CSList::setSelectedItem(RObject item)
{
   if(item == nullref)
   {
      setSelectedIndex(-1);
      return;
   }
   
   for(int i=0; i<count; i++)
   {
      if(items[i] == item)
      {
         setSelectedIndex(i);
         return;
      }
   }
}

int CSList::getSelectedIndex()
{
   return selected;
}

RObject CSList::getSelectedItem()
{
   if(selected == -1)
      return nullref;
   
   return items[selected];
}

int CSList::getVisibleRowCount()
{
   return visCount;
}

void CSList::paintComponent(RGraphics g)
{
   CSComponent::paintComponent(g);
   
   if(!isShowing())
      return;
   
   RInsets ins = getInsets();
   RDimension size = getSize();
   
   int rowWidth = size->width-(ins->left+ins->right);
   int rows = (size->height-(ins->top+ins->bottom))/3;
   
   if(rows > count) rows = count;
   
   int x = ins->left, y = ins->top;
   
   for(int n=visFirst; n<=visLast; n++)
   {
      if(selected == n)
         g->drawString(x+1, y+1, "*");
      
      //g->setHorizontalChar(focused == n ? '=' : '-');
      g->drawString(x+3, y+1, items[n]->toString());
      g->drawRectangle(x, y, rowWidth, 3);
      
      y += 3;
   }
}

RArray<SelectionListener> CSList::getSelectionListeners()
{
   return listeners->getListeners<SelectionListener>();
}

void CSList::addSelectionListener(RSelectionListener l)
{
   listeners->add<SelectionListener>(l);
}

void CSList::removeSelectionListener(RSelectionListener l)
{
   listeners->remove<SelectionListener>(l);
}

void CSList::fireValueChangedEvent()
{
   RSelectionEvent e = new SelectionEvent(thisref, selected, selected);
   
   RArray<util::Listener> arr = listeners->getListeners();
   
   for(int n=0; n<arr->length; n++)
   {
      if(type_of<SelectionListener>(arr[n]))
      {
         RSelectionListener rsl = type_cast<SelectionListener>(arr[n]);
         
         rsl->selectionChanged(e);
      }
   }
}

void CSList::scrollToFocused()
{
   if(focused < visFirst)
   {
      visFirst = focused>0?focused:0;
      visLast = visFirst + (visCount-1);
   }
   else if(focused > visLast)
   {
      visLast = focused;
      visFirst = visLast - (visCount-1);
   }
   
   if(isShowing())
      repaint();
}

int CSList::getWidestElementSize()
{
   int size = 10;
   
   for(int n=0; n<items->length; n++)
   {
      int strSize = items[n]->toString()->length();
      
      if(size < strSize)
         size = strSize;
   }
   
   return size+5; //add 5 for the inner component
}

} /* namespace cui */

} /* namespace aro */
