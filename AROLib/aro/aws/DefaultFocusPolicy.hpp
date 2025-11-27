#ifndef AWS_DEFAULTFOCUSPOLICY_H
#define AWS_DEFAULTFOCUSPOLICY_H

#include <aro/aws/FocusPolicy.hpp>

namespace aro {

namespace aws {

class DefaultFocusPolicy;
typedef Ref<DefaultFocusPolicy> RDefaultFocusPolicy;

class DefaultFocusPolicy extends public Object implements public FocusPolicy
{
   class MutableBool : public Object
   {
      public:
         vbool value;
   };
   
   typedef Ref<MutableBool> RMutableBool;
   
   public:
      static const RMutableBool found;
      
      virtual vbool accept(RComponent comp);
      virtual RComponent getLast(RContainer parent);
      virtual RComponent getFirst(RContainer parent);
      virtual RComponent getDefault(RContainer parent);
      virtual RComponent getNext(RContainer parent, RComponent comp);
      virtual RComponent getPrevious(RContainer parent, RComponent comp);
   
   private:
      RComponent getNext(RContainer parent, RComponent comp, RMutableBool found);
      RComponent getPrevious(RContainer parent, RComponent comp, RMutableBool found);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_DEFAULTFOCUSPOLICY_H */
