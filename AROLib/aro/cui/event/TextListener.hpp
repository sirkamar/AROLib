#ifndef AWSE_TEXTLISTENER_H
#define AWSE_TEXTLISTENER_H

#include <aro/util/Listener.hpp>

namespace aro {

namespace cui {

namespace event {

class TextEvent;
interface TextListener;
typedef Ref<TextEvent> RTextEvent;
typedef Ref<TextListener> RTextListener;

interface TextListener : util::Listener
{
   virtual void textChanged(RTextEvent e)=0;
};

} /* namespace event */

} /* namespace aws */

} /* namespace aro */

#endif /* AWSE_TEXTLISTENER_H */
