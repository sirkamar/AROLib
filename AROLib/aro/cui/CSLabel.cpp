#include <aro/core.h>
#include <aro/cui/CSLabel.h>
#include <aro/aws/Insets.h>
#include <aro/aws/Graphics.h>

namespace aro {

namespace cui {

using namespace aws;

CSLabel::CSLabel()
{
   text = "";
   hTextPos = LEFT;
   vTextPos = CENTER;
}


CSLabel::CSLabel(RString str)
{
   text = str;
   hTextPos = LEFT;
   vTextPos = CENTER;
}

RString CSLabel::getText()
{
   return text;
}

RComponent CSLabel::getLabelFor()
{
   return labelFor;
}

void CSLabel::setText(RString txt)
{
   RString oldText = text;

   text = txt;

   firePropertyChanged("text", oldText, text);

   setDisplayedMnemonicIndex(text->indexOf(getDisplayedMnemonic()));

   if(text == nullref || oldText == nullref || !text->equals(oldText))
   {
      revalidate();
      repaint();
   }
}

int CSLabel::getDisplayedMnemonic()
{
   return mnemonic;
}

RDimension CSLabel::getMinimumSize()
{
   RDimension d = Component::getMinimumSize();
   
   if(d != nullref)
      return d;
   
   RInsets ins = getInsets();
   
   return new Dimension(2+ins->left+ins->right, 1+ins->top+ins->bottom);
}

RDimension CSLabel::getPreferredSize()
{
   RDimension d = Component::getPreferredSize();
   
   if(d != nullref)
      return d;
   
   RInsets ins = getInsets();
   
   int h = mnemonicIndex < 0 ? 1 : 2;
   int w = Math::maximum(text->length(), 2);
   
   return new Dimension(w+ins->left+ins->right, h+ins->top+ins->bottom);
}

int CSLabel::getVerticalTextPosition()
{
   return vTextPos;
}

void CSLabel::setLabelFor(RComponent c)
{
   RComponent oldC = labelFor;
   labelFor = c;
   firePropertyChanged("labelFor", oldC, c);

   // implementation note:
   // if the label's mnemonic is activated
   // the labelFor component's requestFocus
   // member function is to be called
}

int CSLabel::getHorizontalTextPosition()
{
   return hTextPos;
}

int CSLabel::getDisplayedMnemonicIndex()
{
   return mnemonicIndex;
}

void CSLabel::setDisplayedMnemonic(int key)
{
   int oldValue = mnemonic;
   
   mnemonic = key;
   
   firePropertyChanged("displayedMnemonic", new Int(oldValue), new Int(key));
   
   setDisplayedMnemonicIndex(text->indexOf(getDisplayedMnemonic()));
   
   if(oldValue != key)
   {
      revalidate();
      repaint();
   }
}

void CSLabel::setVerticalTextPosition(int pos)
{
   if(pos != TOP && pos != BOTTOM && pos != CENTER)
      ex_throw new ArgumentException("Use CUIConstants text positions "
                                  "TOP, BOTTOM or CENTER only.");
   
   int old = vTextPos;
   vTextPos = pos;
   firePropertyChanged("verticalTextPosition", new Int(old), new Int(hTextPos));
   revalidate();
   repaint();
}

void CSLabel::setHorizontalTextPosition(int pos)
{
   if(pos != LEFT && pos != RIGHT && pos != CENTER)
      ex_throw new ArgumentException("Use CUIConstants text positions "
                                  "LEFT, RIGHT or CENTER only.");
   
   int old = hTextPos;
   hTextPos = pos;
   firePropertyChanged("horizontalTextPosition", new Int(old), new Int(hTextPos));
   revalidate();
   repaint();
}

void CSLabel::setDisplayedMnemonicIndex(int index)
{
   int oldValue = mnemonicIndex;

   if(index == -1)
      mnemonicIndex = -1;
   else
   {
      RString text = getText();
      int textLength = (text == nullref) ? 0 : text->length();

      if(index < -1 || index >= textLength)
         ex_throw new ArgumentException("index == " + String::valueOf(index));
   }

   mnemonicIndex = index;
   firePropertyChanged("displayedMnemonicIndex", new Int(oldValue), new Int(index));

   if(index != oldValue)
   {
      revalidate();
      repaint();
   }
}

void CSLabel::paintComponent(RGraphics g)
{
   CSComponent::paintComponent(g);

   int x, y;
   RInsets in = getInsets();
   int twid = text->length();
   int cwid = getSize()->width - (in->left+in->right);
   int chgt = getSize()->height - (in->top+in->bottom);
   
   if(twid > cwid || hTextPos == LEFT)
      x = in->left;
   else if(hTextPos == CENTER)
      x = in->left + cwid/2 - twid/2;
   else
      x = in->left + cwid - twid;
   
   if(vTextPos == TOP)
      y = in->top;
   else if(vTextPos == CENTER)
      y = in->top + chgt/2;
   else
      y = in->top + chgt - 1;
   
   g->drawString(x, y, text);
}

} /* namespace cui */

} /* namespace aro */
