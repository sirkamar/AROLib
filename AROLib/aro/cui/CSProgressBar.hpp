#ifndef CUI_CSPROGRESSBAR_H
#define CUI_CSPROGRESSBAR_H

#include <aro/cui/CSComponent.hpp>

namespace aro {

namespace cui {

class CSProgressBar;
typedef Ref<CSProgressBar> RCSProgressBar;

class CSProgressBar extends public CSComponent
{
   public:
      static const int HORIZONTAL;
      static const int VERTICAL;
      
      CSProgressBar();
      CSProgressBar(int orient);
      CSProgressBar(int min,int max);
      CSProgressBar(int orient,int min,int max);
      
      virtual void stepUp();
      virtual void stepDown();
      virtual void stepUp(int inc);
      virtual void stepDown(int dec);
      
      virtual void setValue(int val);
      virtual void setOrientation(int orient);
      virtual void setValueRange(int min, int max);
      
      virtual int getValue();
      virtual int getOrientation();
      virtual int getMaximumValue();
      virtual int getMinimumValue();
      virtual int getPercentComplete();
      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getPreferredSize();
   
   protected:
      virtual void paintComponent(aws::RGraphics g);
   
   private:
      int value;
      int min, max;
      int orientation;
      
      RString getProgress();
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSPROGRESSBAR_H */
