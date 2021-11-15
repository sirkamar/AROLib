#include <aro/core.hpp>
#include <aro/io/FileWriter.hpp>
#include <aro/io/FileOutputStream.hpp>

namespace aro {

namespace io {

FileWriter::FileWriter(RString file)
   :OutputStreamWriter(new FileOutputStream(file))
{

}

} /* namespace io */

} /* namespace aro */
