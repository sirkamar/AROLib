#include <aro/core/utils/Foreach.hpp>

namespace aro {

ArgumentException::ArgumentException()
   :ArgumentException("An invalid parameter was passed "
      "to a function that considers invalid parameters erroneous.")
{
   
}

ArgumentException::ArgumentException(RString msg)
   :Exception(msg)
{
   
}

} /* namespace aro */
