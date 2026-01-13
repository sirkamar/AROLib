#include <aro/core/impl/All.hpp>
#include <aro/core/NullException.hpp>

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
