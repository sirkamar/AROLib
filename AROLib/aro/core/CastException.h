#ifndef CORE_CASTEXCEPTION_H
#define CORE_CASTEXCEPTION_H

#include <aro/core/Exception.h>

namespace aro {

class CastException; // forward declaration
typedef Ref<CastException> RCastException;

class CastException : public Exception
{
   public:
      CastException();
      CastException(RString msg);
};

}

#endif /* CORE_CASTEXCEPTION */
