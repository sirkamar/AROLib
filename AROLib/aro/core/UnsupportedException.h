#ifndef CORE_UNSUPPORTEDEXCEPTION_H
#define CORE_UNSUPPORTEDEXCEPTION_H

#include <aro/core/Exception.h>

namespace aro {

class UnsupportedException;
typedef Ref<UnsupportedException> RUnsupportedException;

class UnsupportedException : public Exception
{
   public:
      UnsupportedException();
      UnsupportedException(RString msg);
};

}

#endif /* CORE_UNSUPPORTEDEXCEPTION_H */
