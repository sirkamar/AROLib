#ifndef IO_FILEINPUTSTREAM_H
#define IO_FILEINPUTSTREAM_H

#include <fstream>
#include <aro/io/InputStream.hpp>

namespace aro {

namespace io {

class FileInputStream;
typedef Ref<FileInputStream> RFileInputStream;

class FileInputStream extends public InputStream
{
   public:
      FileInputStream(RString file);
      
      virtual void close();
      
      virtual vint available();
      virtual vlong skip(vlong n);
      
      virtual vint read();
      virtual vint read(RArray<vint> bytes);
      virtual vint read(RArray<vint> bytes,vint offset,vint num);
      
   private:
      std::wifstream file;
      
      void openFile(RString file);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILEINPUTSTREAM_H */
