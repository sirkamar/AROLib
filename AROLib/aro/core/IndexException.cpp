#include <aro/core/utils/Foreach.hpp>
#include <aro/core/IndexException.hpp>

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
