#include <aro/core/impl/All.hpp>

namespace aro {

CastException::CastException()
   :CastException("Type conversion not valid")
{
   
}

CastException::CastException(RString msg)
   :Exception(msg)
{
   
}

} /* namespace aro */
