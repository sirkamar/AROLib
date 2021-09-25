#include <aro/core/utils/Foreach.h>
#include <aro/core/NullException.h>

namespace aro {

NullException::NullException()
   :NullException("Null reference")
{
   
}

NullException::NullException(RString msg)
   :Exception(msg)
{
   
}

} /* namespace aro */
