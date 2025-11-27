#ifndef CUI_CSTEXTAREA_H
#define CUI_CSTEXTAREA_H

#include <aro/cui/CSTextcomponent.hpp>

namespace aro {

namespace cui {

class CSTextArea;
typedef Ref<CSTextArea> RCSTextArea;

class CSTextArea extends public CSTextComponent
{
   public:
      static const vint NO_WRAP = 0;
      static const vint LINE_WRAP = 1;
      static const vint WORD_WRAP = 2;
      
      CSTextArea();
      CSTextArea(RString text);
      CSTextArea(int rows,int cols);
      CSTextArea(RString text, int rows, int cols);
      
      virtual aws::RDimension getPreferredSize();
      virtual aws::RDimension getMinimumSize();
      virtual void setWrapStyle(vint style);
      virtual void setColumns(int cols);
      virtual void append(RString str);
      virtual void setRows(int rows);
      virtual vint getWrapStyle();
      virtual vint getColumns();
      virtual vint getRows();
   
   protected:
      virtual void paintComponent(aws::RGraphics g);
      virtual void processKeyEvent(aws::event::RKeyEvent e);
   
   private:
      vint wrapStyle;
      int rows, cols;
      bool isMod;
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSTEXTAREA_H */