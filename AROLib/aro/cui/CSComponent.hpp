#ifndef CUI_CSCOMPONENT_H
#define CUI_CSCOMPONENT_H

#include <aro/aws/Container.hpp>
#include <aro/cui/border/Border.hpp>

namespace aro {

namespace cui {

using namespace border;

class CSComponent : public aws::Container
{
   public:
      CSComponent();
      
      virtual RBorder getBorder();
      virtual aws::RInsets getInsets();
      virtual void setEnabled(vbool b);
      virtual void setVisible(vbool b);
      virtual void setBorder(RBorder b);
      virtual void paint(aws::RGraphics g);
      virtual void update(aws::RGraphics g);
      
      virtual aws::RDimension getPreferredSize();
      virtual aws::RDimension getMinimumSize();
      virtual aws::RDimension getMaximumSize();

   protected:
      RBorder border;
      
      virtual void paintBorder(aws::RGraphics g);
      virtual void paintChildren(aws::RGraphics g);
      virtual void paintComponent(aws::RGraphics g)=0;
      virtual void processKeyEvent(aws::event::RKeyEvent e);
      virtual void processComponentKeyEvent(aws::event::RKeyEvent e);
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSCOMPONENT_H */

