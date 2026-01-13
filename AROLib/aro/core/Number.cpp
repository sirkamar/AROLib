#include <aro/core/Number.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

vshort Number::shortValue()
{
   return static_cast<vshort>(intValue());
}

} /* namespace aro */