#include <aro/core.h>
#include <aro/io/FileWriter.h>
#include <aro/io/FileOutputStream.h>

namespace aro {

namespace io {

FileWriter::FileWriter(RString file)
   :OutputStreamWriter(new FileOutputStream(file))
{

}

} /* namespace io */

} /* namespace aro */
