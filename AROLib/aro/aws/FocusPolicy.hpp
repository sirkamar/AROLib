#ifndef AWS_FOCUSPOLICY_H
#define AWS_FOCUSPOLICY_H

#include <aro/aws/Container.hpp>

namespace aro {

namespace aws {

interface FocusPolicy;
typedef Ref<FocusPolicy> RFocusPolicy;

interface FocusPolicy : Interface
{
   virtual RComponent getLast(RContainer parent)=0;
   virtual RComponent getFirst(RContainer parent)=0;
   virtual RComponent getDefault(RContainer parent)=0;
   virtual RComponent getNext(RContainer parent, RComponent comp)=0;
   virtual RComponent getPrevious(RContainer parent, RComponent comp)=0;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_FOCUSPOLICY_H */
