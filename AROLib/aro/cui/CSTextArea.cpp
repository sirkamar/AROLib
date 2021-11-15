#include <aro/core.hpp>
#include <aro/aws/Insets.hpp>
#include <aro/cui/CSTextArea.hpp>
#include <aro/aws/event/KeyEvent.hpp>
#include <aro/cui/border/LineBorder.hpp>

namespace aro {

namespace cui {

using namespace aws;
using namespace aws::event;

CSTextArea::CSTextArea()
   :CSTextArea("")
{
   //isMod = false;
   //cols = rows = 30;
   //wrapStyle = WrapStyle::NO_WRAP;
   //setBorder(new LineBorder());
}

CSTextArea::CSTextArea(RString str)
   :CSTextArea(str, 30, 30)
{
   //isMod = false;
   //cols = rows = 30;
   //wrapStyle = WrapStyle::NO_WRAP;
   //setBorder(new LineBorder());
}

CSTextArea::CSTextArea(int r, int c)
   :CSTextArea("", r, c)
{
   //if(r < 0)
   //   ex_throw new ArgumentException("rows less than zero");
   //
   //if(c < 0)
   //   ex_throw new ArgumentException("columns less than zero");
   //
   //isMod = false;
   //cols = c; rows = r;
   //wrapStyle = WrapStyle::NO_WRAP;
   //setBorder(new LineBorder());
}

CSTextArea::CSTextArea(RString str, int r, int c)
   :CSTextComponent(str)
{
   if(r < 0)
      ex_throw new ArgumentException("rows less than zero");
   
   if(c < 0)
      ex_throw new ArgumentException("columns less than zero");
   
   isMod = false;
   cols = c; rows = r;
   wrapStyle = NO_WRAP;
   border = new LineBorder();
}

void CSTextArea::setRows(int rows)
{
   if(rows < 0)
      ex_throw new ArgumentException("rows less than zero");
   
   if(thisref->rows != rows)
   {
      thisref->rows = rows;
      invalidate();
   }
}

void CSTextArea::setColumns(int cols)
{
   if(cols < 0)
      ex_throw new ArgumentException("columns less than zero");
   
   if(thisref->cols != cols)
   {
      thisref->cols = cols;
      invalidate();
   }
}

void CSTextArea::setWrapStyle(vint style)
{
   vbool old = wrapStyle;
   
   switch(style)
   {
      case NO_WRAP:
      case LINE_WRAP:
      case WORD_WRAP:
         wrapStyle = style;
         break;
      
      default:
         ex_throw new ArgumentException("Invalid wrap style for CSTextArea: " + String::valueOf(style));
   }
   
   firePropertyChanged("wrapStyle", new Bool(old), new Bool(wrapStyle));
   
   if(isShowing())
      repaint();
}

vint CSTextArea::getWrapStyle()
{
   return wrapStyle;
}

RDimension CSTextArea::getPreferredSize()
{
   RDimension d = CSTextComponent::getPreferredSize();
   
   if(d != nullref)
      return d;
   
   RInsets ins = getInsets();
   
   int w = Math::maximum(30, cols), h = Math::maximum(30, rows);
   
   return new Dimension(w+ins->left+ins->right, h+ins->top+ins->bottom);
}

RDimension CSTextArea::getMinimumSize()
{
   RDimension d = CSTextComponent::getMinimumSize();
   
   if(d != nullref)
      return d;
   
   RInsets ins = getInsets();
   
   return new Dimension(2+ins->left+ins->right, 1+ins->top+ins->bottom);
}

void CSTextArea::append(RString str)
{
   text->append(str);
   
   if(isShowing())
      repaint();
}

int CSTextArea::getColumns()
{
   return cols;
}

int CSTextArea::getRows()
{
   return rows;
}

void CSTextArea::paintComponent(RGraphics g)
{
   CSTextComponent::paintComponent(g);
   
   if(!isShowing())
      return;
   
   RDimension d = getSize();
   RInsets ins = getInsets();
   int x = ins->left, y = ins->top;
   int wdt = d->width-(ins->left+ins->right);
   int hgt = d->height-(ins->top+ins->bottom);
   
   int pos;
   RString temp = text->toString();
   
   do
   {
      pos = temp->indexOf(KeyEvent::VKEY_ENTER);
      int len = temp->length();
      bool b = pos > -1;
      
      if(pos > wdt || (pos < 0 && len > wdt))
      {
         if(wrapStyle == LINE_WRAP)
            pos = wdt;
         
         else if(wrapStyle == WORD_WRAP)
         {
            pos = temp->lastIndexOf(' ', wdt);
            if(pos < 0)
               pos = wdt;
            else
            {
               b = false;
               if(pos < wdt) pos++;
            }
         }
      }
      
      if(pos > -1)
      {
         g->drawString(x,y,temp->substring(0,pos));
         temp = temp->substring(b?pos+1:pos);
      }
      else
         g->drawString(x,y,temp);
   }
   while(pos > -1 && y++ < hgt);
}

void CSTextArea::processKeyEvent(RKeyEvent e)
{
   int eventID = e->getEventID();
   
   if(eventID == KeyEvent::KEY_TYPED)
   {
      char c = e->getKeyChar();
      
      if(isEditable())
      {
         if(c == KeyEvent::VKEY_BACKSPACE)
            text->setLength(text->length() - 1);
         else
            text->append(String::valueOf(c));
         
         // prevent passing on
         // to key listeners
         e->consume();
         
         repaint();
      }
   }
}

} /* namespace cui */

} /* namespace aro */
