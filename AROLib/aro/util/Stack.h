#ifndef UTIL_STACK_H
#define UTIL_STACK_H

#include <aro/util/Vector.h>

namespace aro {

namespace util {

template <class T> class Stack;

template <class T>
using RStack = Ref<Stack<T>>;

/**
 * Stack class template declaration
 */ 
template <class T>
class Stack : public Vector<T>
{
   public:
      Ref<T> pop();
      Ref<T> peek();
      void push(Ref<T> e);
      vint search(Ref<T> e);
};


// Stack class template implementation

template <class T>
Ref<T> Stack<T>::pop()
{
   sync_lock(thisref)
   {
      Ref<T> obj = peek();
      
      removeElementAt(size()-1);
      
      return obj;
   }
   
}

template <class T>
Ref<T> Stack<T>::peek()
{
   sync_lock(thisref)
   {
      vint len = size();
      
      if(len == 0)
         ex_throw new StateException("Stack is empty");
   
      Ref<T> retVal = elementAt(len-1);
      
      return retVal;
   }
   
}

template <class T>
void Stack<T>::push(Ref<T> obj)
{
   addElement(obj);
}

template <class T>
vint Stack<T>::search(Ref<T> obj)
{
   sync_lock(thisref)
   {
      vint pos = lastIndexOf(obj);
      
      if(pos >= 0)
         pos = size() - pos;
      
      return pos;
   }
}

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_STACK_H */
