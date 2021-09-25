#ifndef IO_IOEXCEPTION_H
#define IO_IOEXCEPTION_H

#include <aro/core/Exception.h>

namespace aro {

namespace io {

class IOException; // forward declaration
typedef Ref<IOException> RIOException;

/** IOExceptions are thrown to indicate
 * that an error has occured while
 * performing an I/O operation. */
class IOException : public Exception
{
   public:
      IOException();
      IOException(RString msg);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_IOEXCEPTION_H */
