#include <aro/core/utils/Foreach.hpp>
#include <aro/core/StateException.hpp>

namespace aro {

StateException::StateException()
   :StateException("Invalid object state")
{
   
}

StateException::StateException(RString msg)
   :Exception(msg)
{
   
}

} /* namespace aro */
