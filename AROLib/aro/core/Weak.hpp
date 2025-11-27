/******************************************************************************
*                   COMMON OBJECTS AND METHODS (COM) PACKAGE                  *
*******************************************************************************
* Name        | class Weak<T>                                                *
*             |                                                               *
* Author      | Kamar Morris                                                  *
*             |                                                               *
* Version     | 1.0                                                           *
*             |                                                               *
* Description | The template class Weak represents a weak reference to an    *
*             | Object. The reference is consider to be weak because the link *
*             | to an Object is not tracked by the Garbage Collector and thus *
*             | will not prevent the automatic deletion of memory allocated to*
*             | it. This is useful especially to prevent circular links where *
*             | two objects each holds a reference to the other and prevents  *
*             | either from being deleted even when neither is ever used nor  *
*             | are there any other active references to them remaining. When *
*             | such a situation arrise where objects need to reference each  *
*             | other it is more appropriate for one or both such references  *
*             | to be implemented using weak references.                      *
*             |                                                               *
*             | Since a weak reference does not affect the garbage collection *
*             | process a RWeak variable cannot be initialized directly as    *
*             | is done with a Ref variable. To be linked via a RWeak it is   *
*             | expected that an object would've already be linked with a Ref *
*             | variable which is then used to initialize the RWeak. To use   *
*             | a RWeak it must first be assigned to a regular Ref variable.  *
*             | If the linked object gets deleted then the RWeak returns a    *
*             | null Ref when it is assigned.                                 *
*             |                                                               *
*             |                                                               *
*             | Usage example:                                                *
*             | RObject obj = new Object();                                   *
*             | RWeak<Object> weakObj = new Weak<Object>(obj);                *
*             |                                                               *
*             | RObject obj2 = weakObj->get();                                *
*             | if(obj2 != nullref)                                           *
*             |    obj2->toString();                                          *
*             |                                                               *
*             | See API documention for complete details.                     *
*             |                                                               *
*******************************************************************************
*                             REVISION HISTORY                                *
*******************************************************************************
* Date        Author         Version   Description                            *
* ----------  ---------      -------   -----------                            *
* YYYY/MM/DD  X. XXXXXX        X.X                                            *
*                                                                             *
* 2008/03/15  K. Morris        1.0     Created class.                         *
*                                                                             *
******************************************************************************/
#ifndef CORE_WEAK_H
#define CORE_WEAK_H

#include <aro/core/Null.hpp>

namespace aro {

template <class T>
using RWeak = Ref<Weak<T>>;

template <class T>
class Weak extends public Object
{
   public:
      Weak(const Ref<T>& ref);
      
      RString toString();
      
      Ref<T> get();
   
   private:
      T* ref;
};

} /* namespace aro */

#endif /* CORE_WEAK_H */
