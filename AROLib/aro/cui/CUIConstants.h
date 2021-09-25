#ifndef CUI_CUICONSTANTS_H
#define CUI_CUICONSTANTS_H

#include <aro/core/Interface.h>

namespace aro {

namespace cui {

interface CUIConstants;
typedef Ref<CUIConstants> RCUIConstants;

interface CUIConstants : Interface
{
   // used for both compass-direction
   // as well as box-orientation
   static const int CENTER       = 0;
   
   // box-orienatation constants
   static const int TOP          = 1;
   static const int LEFT         = 2;
   static const int BOTTOM       = 3;
   static const int RIGHT        = 4;
   
   // compass-directions
   static const int NORTH        = 5;
   static const int EAST         = 6;
   static const int SOUTH        = 7;
   static const int WEST         = 8;
   
   // layout, or scrolling axis
   static const int VERTICAL     = 0;
   static const int HORIZONTAL   = 1;
   
   // sequence directions
   static const int NEXT         = 12;
   static const int PREVIOUS     = 13;
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CUICONSTANTS_H */
