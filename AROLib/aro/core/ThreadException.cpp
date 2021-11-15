#include <aro/core/utils/Foreach.hpp>
#include <aro/core/ThreadException.hpp>

namespace aro {

ThreadException::ThreadException()
   :ThreadException("Thread failed")
{
   
}

ThreadException::ThreadException(RString msg)
   :Exception(msg)
{
   
}

} /* namespace aro */
