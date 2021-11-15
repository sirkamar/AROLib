#include <aro/core.hpp>
#include <aro/io/FileReader.hpp>
#include <aro/io/FileInputStream.hpp>

namespace aro {

namespace io {

FileReader::FileReader(RString file)
   :InputStreamReader(new FileInputStream(file))
{

}

} /* namespace io */

} /* namespace aro */
