#include <aro/core/utils/Foreach.h>
#include <aro/core/IndexException.h>

namespace aro {

IndexException::IndexException()
   :Exception("Invalid Index Operation")
{
   
}

IndexException::IndexException(vint index)
   :Exception("Invalid Index: " + String::valueOf(index))
{
   
}

IndexException::IndexException(RString msg)
   :Exception(msg)
{
   
}

IndexException::IndexException(RString msg, vint index)
   :Exception(msg + String::valueOf(index))
{
   
}

} /* namespace aro */
