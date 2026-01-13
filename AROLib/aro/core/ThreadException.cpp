#include <aro/core/impl/All.hpp>
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
