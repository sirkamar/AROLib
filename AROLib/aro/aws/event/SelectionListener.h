#ifndef AWSE_SELECTIONLISTENER_H
#define AWSE_SELECTIONLISTENER_H

#include <aro/util/Listener.h>

namespace aro {

namespace aws {

namespace event {

class SelectionEvent;
interface SelectionListener;
typedef Ref<SelectionEvent> RSelectionEvent;
typedef Ref<SelectionListener> RSelectionListener;

interface SelectionListener : util::Listener
{
   virtual void selectionChanged(RSelectionEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_SELECTIONLISTENER_H */
