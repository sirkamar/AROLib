#include <aro/core.hpp>
#include <aro/cui/CSProgressBar.hpp>
#include <aro/cui/border/LineBorder.hpp>

namespace aro {

namespace cui {

using namespace aws;

const int CSProgressBar::HORIZONTAL = 1;
const int CSProgressBar::VERTICAL = 0;

CSProgressBar::CSProgressBar()
   :CSProgressBar(HORIZONTAL)
{
   //max = 100;
   //min = value = 0;
   //setFocusable(false);
   //orientation = HORIZONTAL;
   //setBorder(new LineBorder());
}

CSProgressBar::CSProgressBar(int orient)
   :CSProgressBar(orient, 0, 100)
{
   //if(orient < VERTICAL || orient > HORIZONTAL)
   //   ex_throw new ArgumentException(String::valueOf(orient) +
   //                               " is not a legal orientation");
   //
   //max = 100;
   //min = value = 0;
   //setFocusable(false);
   //orientation = orient;
   //setBorder(new LineBorder());
}

CSProgressBar::CSProgressBar(int min, int max)
   :CSProgressBar(HORIZONTAL, min, max)
{
   //if(max <= min)
   //   ex_throw new ArgumentException("Maximum value must "
   //                               "be greater than minimum.");
   //
   //value = min;
   //setFocusable(false);
   //orientation = HORIZONTAL;
   //setBorder(new LineBorder());
   //thisref->min = min; thisref->max = max;
}

CSProgressBar::CSProgressBar(int orient, int min, int max)
{
   if(orient < VERTICAL || orient > HORIZONTAL)
      ex_throw new ArgumentException(String::valueOf(orient) +
                                  " is not a legal orientation");
   
   if(max <= min)
      ex_throw new ArgumentException("Maximum value must "
                                  "be greater than minimum.");
   
   value = min;
   thisref->min = min;
   thisref->max = max;
   setFocusable(false);
   orientation = orient;
   border = new LineBorder();
}

void CSProgressBar::stepUp()
{
   stepUp(1);
}

void CSProgressBar::stepDown()
{
   stepDown(1);
}

void CSProgressBar::stepUp(int step)
{
   if(step < 0)
      ex_throw new ArgumentException("Invalid stepDown value: " +
                                   String::valueOf(step));
   
   if(value == max)
      return;
   
   value = value+step>max ? max : value+step;
   
   if(isShowing())
      repaint();
}

void CSProgressBar::stepDown(int step)
{
   if(step < 0)
      ex_throw new ArgumentException("Invalid stepDown value: " +
                                   String::valueOf(step));
   
   if(value == min)
      return;
   
   value = value-step<min ? min : value-step;
   
   if(isShowing())
      repaint();
}

void CSProgressBar::setValue(int val)
{
   if(val > max)
      value = max;
   else if(val < min)
      value = min;
   else
      value = val;
   
   if(isShowing())
      repaint();
}

void CSProgressBar::setOrientation(int orient)
{
   if(orient < VERTICAL || orient > HORIZONTAL)
      ex_throw new ArgumentException(String::valueOf(orient) +
                                  " is not a legal orientation");
   if(orientation != orient)
   {
      orientation = orient;
      
      if(isShowing())
         revalidate();
   }
}

void CSProgressBar::setValueRange(int min, int max)
{
   if(max <= min)
      ex_throw new ArgumentException("Maximum value must "
                                  "be greater than minimum.");
   
   thisref->min = min;
   thisref->max = max;
}

int CSProgressBar::getValue()
{
   return value;
}

int CSProgressBar::getOrientation()
{
   return orientation;
}

int CSProgressBar::getMaximumValue()
{
   return max;
}

int CSProgressBar::getMinimumValue()
{
   return min;
}

RDimension CSProgressBar::getMinimumSize()
{
   if(orientation == HORIZONTAL)
      return new Dimension(6,3);
   
   return new Dimension(3,6);
}

RDimension CSProgressBar::getPreferredSize()
{
   if(orientation == HORIZONTAL)
      return new Dimension(17, 3);
   
   return new Dimension(3, 17);
}

int CSProgressBar::getPercentComplete()
{
   return (value - min) * 100 / (max - min);
}

void CSProgressBar::paintComponent(RGraphics g)
{
   CSComponent::paintComponent(g);
   
   if(!isShowing())
      return;
   
   RDimension size = getSize();
   
   if(orientation == HORIZONTAL)
   {
      g->drawString(1,size->height/2,getProgress());
      
      if(size->width < 8) return;
      
      g->drawVerticalLine(5, 1, size->height-2);
      
      int maxBars = size->width-7;
      int bars =  value * maxBars / max;
      RString progress = "";
      
      for(int n=0; n<bars; n++)
         progress += "*";
      
      g->drawString(6, size->height/2, progress);
   }
   else
   {
      RString str = getProgress();
      int len = str->length();
      
      for(int n=0; n<len; n++)
      {
         char c = str->charAt(n);
         
         g->drawString(size->width/2,n+1,String::valueOf(c));
      }
      
      if(size->height < 8) return;
      
      g->drawHorizontalLine(1, 5, size->width-2);
      
      int maxBars = size->height-7;
      int bars = value * maxBars / max;
      
      for(int n=0; n<bars; n++)
         g->drawString(size->width/2,n+6,"*");
   }
}

RString CSProgressBar::getProgress()
{
   return String::valueOf(getPercentComplete()) + "%";
}

} /* namespace cui */

} /* namespace aro */
