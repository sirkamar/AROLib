#include <aro/core/utils/Foreach.h>
#include <aro/core/UnsupportedException.h>

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
