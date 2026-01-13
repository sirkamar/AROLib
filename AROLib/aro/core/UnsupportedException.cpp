#include <aro/core/impl/All.hpp>
#include <aro/core/UnsupportedException.hpp>

namespace aro {

UnsupportedException::UnsupportedException()
   :UnsupportedException("Unsupported Operation")
{
   
}

UnsupportedException::UnsupportedException(RString msg)
   :Exception(msg)
{
   
}

} /* namespace aro */
