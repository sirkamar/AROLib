#ifndef CORE_THREADEXCEPTION_H
#define CORE_THREADEXCEPTION_H

#include <aro/core/Exception.hpp>

namespace aro {

class ThreadException; // forward declaration
typedef Ref<ThreadException> RThreadException;

class ThreadException extends public Exception
{
   public:
      ThreadException();
      ThreadException(RString msg);
};

} /* namespace aro */

#endif /* CORE_THREADEXCEPTION_H */
