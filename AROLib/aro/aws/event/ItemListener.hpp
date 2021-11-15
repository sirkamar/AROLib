#ifndef AWSE_ITEMLISTNER_H
#define AWSE_ITEMLISTNER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace aws {

namespace event {

class ItemEvent;
interface ItemListener;
typedef Ref<ItemEvent> RItemEvent;
typedef Ref<ItemListener> RItemListener;

interface ItemListener : util::Listener
{
   virtual void itemStateChanged(RItemEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_ITEMLISTNER_H */
