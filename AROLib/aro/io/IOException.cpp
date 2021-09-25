#include <aro/io/IOException.h>

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
