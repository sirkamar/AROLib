#ifndef IO_FILEREADER_H
#define IO_FILEREADER_H

#include <aro/io/InputStreamReader.hpp>

namespace aro {

namespace io {

class FileReader;
typedef Ref<FileReader> RFileReader;

class FileReader extends public InputStreamReader
{
   public:
      FileReader(RString file);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILEREADER_H */
