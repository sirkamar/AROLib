#include <aro/aws/Insets.h>
#include <aro/aws/Graphics.h>
#include <aro/aws/Component.h>
#include <aro/cui/border/TitleBorder.h>

namespace aro {

using namespace aws;

namespace cui {

namespace border {

TitleBorder::TitleBorder()
   :TitleBorder("")
{
   
}

TitleBorder::TitleBorder(RString text)
   :TitleBorder(nullref, text)
{
   
}
TitleBorder::TitleBorder(RBorder border)
   :TitleBorder(border, "")
{
   
}

TitleBorder::TitleBorder(RBorder aBorder, RString text)
   :TitleBorder(aBorder, text, LEFT)
{
   
}

TitleBorder::TitleBorder(RBorder aBorder, RString text, vint alignment)
{
   title = text;
   border = aBorder;

   setTitleAlignment(alignment);
}

RString TitleBorder::getTitle()
{
   return title;
}

void TitleBorder::setTitle(RString text)
{
   title = text;
}

RBorder TitleBorder::getBorder()
{
   return border;
}

void TitleBorder::setBorder(RBorder newBorder)
{
   border = newBorder;
}

vint TitleBorder::getTitleAlignment()
{
   return titleAlignment;
}

void TitleBorder::setTitleAlignment(vint alignment)
{
   switch(alignment)
   {
      case LEFT:
      case CENTER:
      case RIGHT:
         titleAlignment = alignment;
         break;
      
      default:
         ex_throw new ArgumentException(String::valueOf(alignment) + " is not a valid title alignment");
   }
   
}

RInsets TitleBorder::getInsets(RInsets insets)
{
   insets = getInsets(border, insets);
   
   if(title != nullref && title->isEmpty())
   {
      vint edge = 0;// type_of<TitleBorder>(border) ? 0 : 2;
      vint titleHeight = 1;

      if(insets->top < titleHeight)
         insets->top = titleHeight - edge;
      
      insets->top += edge + 2;
      insets->left += edge + 2;
      insets->right += edge + 2;
      insets->bottom += edge + 2;
   }

   return insets;
}

void TitleBorder::paintBorder(RComponent c, RGraphics g,
                              vint x, vint y, vint width, vint height)
{
   if(title != nullref && !title->isEmpty())
   {
      RInsets insets = getInsets(border, new Insets());
      vint edge = 0;// type_of<TitleBorder>(border) ? 0 : 2;
      vint titleWidth = title->length(), titleHeight = 1;
      
      vint borderX = x + edge;
      vint borderY = y + edge;
      vint borderW = width - edge - edge;
      vint borderH = height - edge - edge;

      vint titleY = y;
      vint titleH = titleHeight;

      insets->top = edge + insets->top/2 + titleH/2;

      if(insets->top < edge)
      {
         borderY -= insets->top;
         borderH += insets->top;
      }
      else
         titleY += insets->top;
      
      insets->left += edge + 2;
      insets->right += edge + 2;
      
      vint titleX = x;
      vint titleW = width - insets->left - insets->right;

      if(titleW > titleWidth)
         titleW = titleWidth;
      
      switch(titleAlignment)
      {
         case LEFT:
            titleX += insets->left;
            break;
         
         case CENTER:
            titleX += width - insets->right - titleW;
            break;
         
         case RIGHT:
            titleX += (width - titleW) / 2;
            break;
      }
      
      if(border != nullref)
         border->paintBorder(c, g, borderX, borderY, borderW, borderH);
      
      g->drawString(titleX, titleY, title);
   }
   else if(border != nullref)
   {
      border->paintBorder(c, g, x, y, width, height);
   }
}

RInsets TitleBorder::getInsets(RBorder border, RInsets insets)
{
   if(border == nullref)
      insets->set(0,0,0,0);
   else if(type_of<AbstractBorder>(border))
   {
      RAbstractBorder ab = type_cast<AbstractBorder>(border);
      
      insets = ab->getInsets(insets);
   }
   else
   {
      RInsets ins = border->getInsets();
      
      insets->set(ins->top, ins->left, ins->bottom, ins->right);
   }

   return insets;
}

} /* namespace border */

} /* namespace aws */

} /* namespace aro */
