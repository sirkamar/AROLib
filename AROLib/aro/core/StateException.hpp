#ifndef CORE_STATEEXCEPTION_H
#define CORE_STATEEXCEPTION_H

#include <aro/core/Exception.hpp>

namespace aro {

class StateException; // forward declaration
typedef Ref<StateException> RStateException;

class StateException : public Exception
{
   public:
      StateException();
      StateException(RString msg);
};

}

#endif /* CORE_STATEEXCEPTION_H */
