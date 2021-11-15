#ifndef CUI_BORDER_TITLEBORDER_H
#define CUI_BORDER_TITLEBORDER_H

#include <aro/cui/border/AbstractBorder.hpp>

namespace aro {

namespace cui {

namespace border {

class TitleBorder;
typedef Ref<TitleBorder> RTitleBorder;

class TitleBorder : public AbstractBorder
{
   public:
      TitleBorder();
      
      TitleBorder(RString title);
      
      TitleBorder(RBorder border);

      TitleBorder(RBorder border, RString title);

      TitleBorder(RBorder border, RString title, vint titleAlignment);

      virtual RString getTitle();
      
      virtual RBorder getBorder();

      virtual vint getTitleAlignment();
      
      virtual void setTitle(RString title);
      
      virtual void setBorder(RBorder border);
      
      virtual void setTitleAlignment(vint titleAlignment);
      
      virtual aws::RInsets getInsets(aws::RInsets insets);
      
      virtual void paintBorder(aws::RComponent comp, aws::RGraphics g,
                             vint x, vint y, vint width, vint height);
      
      static const vint LEFT = 1, CENTER = 2, RIGHT = 3;
   
   private:
      RString title;
      RBorder border;
      vint titleAlignment;
      
      static aws::RInsets getInsets(RBorder border, aws::RInsets insets);
};

} /* namespace border */

} /* namespace aws */

} /* namespace aro */


#endif /* CUI_BORDER_TITLEBORDER_H */
