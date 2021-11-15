#ifndef CUI_CSLIST_H
#define CUI_CSLIST_H

#include <aro/cui/CSComponent.hpp>
#include <aro/aws/event/SelectionListener.hpp>

namespace aro {

namespace cui {

class CSList;
typedef Ref<CSList> RCSList;

class CSList : public CSComponent
{
   public:
      CSList();
      CSList(RArray<Object> data);
      
      virtual int getSelectedIndex();
      virtual RObject removeItem(int);
      virtual int getVisibleRowCount();
      virtual RObject getSelectedItem();
      virtual void handleInput(int key);
      virtual void addItem(RObject item);
      virtual void removeItem(RObject item);
      virtual void setSelectedIndex(int index);
      virtual aws::RDimension getMinimumSize();
      virtual void setVisibleRowCount(int rows);
      virtual aws::RDimension getPreferredSize();
      virtual void setSelectedItem(RObject item);
      virtual void addItem(RObject item,int index);
      virtual void addSelectionListener(aws::event::RSelectionListener l);
      virtual RArray<aws::event::SelectionListener> getSelectionListeners();
      virtual void removeSelectionListener(aws::event::RSelectionListener l);
   
   protected:
      virtual void fireValueChangedEvent();
      virtual void paintComponent(aws::RGraphics g);

   private:
      int count;
      int focused;
      int visLast;
      int selected;
      int visCount;
      int visFirst;
      RArray<Object> items;
      
      void scrollToFocused();
      int getWidestElementSize();
};

} /* namespace cui */

} /* namespace aro */

#endif /* CUI_CSLIST_H */
