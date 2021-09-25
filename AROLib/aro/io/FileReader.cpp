#include <aro/core.h>
#include <aro/io/FileReader.h>
#include <aro/io/FileInputStream.h>

namespace aro {

namespace io {

FileReader::FileReader(RString file)
   :InputStreamReader(new FileInputStream(file))
{

}

} /* namespace io */

} /* namespace aro */
