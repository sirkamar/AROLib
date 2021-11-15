#include <aro/core/Number.hpp>
#include <aro/core/utils/Foreach.hpp>

namespace aro {

vshort Number::shortValue()
{
   return static_cast<vshort>(intValue());
}

} /* namespace aro */