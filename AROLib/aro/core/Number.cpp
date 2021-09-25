#include <aro/core/Number.h>
#include <aro/core/utils/Foreach.h>

namespace aro {

vshort Number::shortValue()
{
   return static_cast<vshort>(intValue());
}

} /* namespace aro */