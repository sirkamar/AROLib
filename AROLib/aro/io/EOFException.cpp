#include <aro/io/EOFException.hpp>

namespace aro {

namespace io {

EOFException::EOFException()
   :EOFException("End-Of-File")
{
   
}

EOFException::EOFException(RString str)
   :IOException(str)
{
   
}

} /* namespace io */

} /* namespace aro */
