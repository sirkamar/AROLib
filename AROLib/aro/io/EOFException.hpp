#ifndef IO_EOFEXCEPTION_H
#define IO_EOFEXCEPTION_H

#include <aro/io/IOException.hpp>

namespace aro {

namespace io {

class EOFException; // forward declaration
typedef Ref<EOFException> REOFException;

/** An EOFException is thrown to indicate
  that an error has occured while
  performing an I/O operation. */
class EOFException extends public IOException
{
   public:
      EOFException();
      EOFException(RString msg);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_EOFEXCEPTION_H */
