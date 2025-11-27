#

#ifndef AWS_SELECTABLE_H
#define AWS_SELECTABLE_H

#include <aro/aws/event/ItemListener.hpp>

namespace aro {

namespace aws {

interface Selectable;
typedef Ref<Selectable> RSelectable;

interface Selectable extends Interface
{
   virtual RArray<Object> getSelectedObjects()=0;
   virtual void addItemListener(event::RItemListener l)=0;
   virtual void removeItemListener(event::RItemListener l)=0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_SELECTABLE_H */
