#ifndef CORE_ARGUMENTEXCEPTION_H
#define CORE_ARGUMENTEXCEPTION_H

#include <aro/core/Exception.hpp>

namespace aro {

class ArgumentException; // forward declaration
typedef Ref<ArgumentException> RArgumentException;

/** An ArgumentException is thrown to indicate that
 * an argument (i.e. parameter) is not valid */
class ArgumentException extends public Exception
{
   public:
      ArgumentException();
      ArgumentException(RString msg);
};

}

#endif /* CORE_ARGUMENTEXCEPTION_H */
