#include <aro/core/utils/Foreach.h>
#include <aro/core/ThreadException.h>

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
