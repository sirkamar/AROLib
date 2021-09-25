#include <aro/core/utils/Foreach.h>
#include <aro/core/StateException.h>

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
