#include <aro/io/IOException.hpp>

namespace aro {

namespace io {

IOException::IOException()
   :Exception("Input/Output error")
{
   
}

IOException::IOException(RString str)
   :Exception(str)
{
   
}

} /* namespace io */

} /* namespace aro */
