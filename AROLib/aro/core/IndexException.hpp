#ifndef CORE_INDEXEXCEPTION_H
#define CORE_INDEXEXCEPTION_H

#include <aro/core/Exception.hpp>

namespace aro {

class IndexException; // forward declaration
typedef Ref<IndexException> RIndexException;

class IndexException extends public Exception
{
   public:
      IndexException();
      IndexException(vint index);
      IndexException(RString msg);
      IndexException(RString msg, vint index);
};

}

#endif /* CORE_INDEXEXCEPTION_H */
