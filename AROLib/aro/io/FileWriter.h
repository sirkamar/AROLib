#ifndef IO_FILEWRITER_H
#define IO_FILEWRITER_H

#include <aro/io/OutputStreamWriter.h>

namespace aro {

namespace io {

class FileWriter;
typedef Ref<FileWriter> RFileWriter;

class FileWriter : public OutputStreamWriter
{
   public:
      FileWriter(RString file);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILEWRITER_H */
