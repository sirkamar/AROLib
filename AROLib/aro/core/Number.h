#ifndef CORE_NUMBER_H
#define CORE_NUMBER_H

#include <aro/core/String.h>

namespace aro {

class Number;
typedef Ref<Number> RNumber;

class Number : public Object
{
   public:
      virtual vshort shortValue();
      
      virtual vint intValue() = 0;
      virtual vlong longValue() = 0;
      
      virtual vfloat floatValue() = 0;
      virtual vdouble doubleValue() = 0;
};

} /* namespace aro */

#endif /* CORE_NUMBER_H */
