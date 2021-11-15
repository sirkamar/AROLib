#ifndef CORE_NULLEXCEPTION_H
#define CORE_NULLEXCEPTION_H

#include <aro/core/Exception.hpp>

namespace aro {

class NullException; // forward declaration
typedef Ref<NullException> RNullException;

class NullException : public Exception
{
   public:
      NullException();
      NullException(RString msg);
};

} /* namespace aro */

#endif /* CORE_NULLEXCEPTION_H */
