#ifndef IO_FILEOUTPUTSTREAM_H
#define IO_FILEOUTPUTSTREAM_H

#include <fstream>
#include <aro/io/OutputStream.hpp>

namespace aro {

namespace io {

class FileOutputStream;
typedef Ref<FileOutputStream> RFileOutputStream;

class FileOutputStream : public OutputStream
{
   public:
      FileOutputStream(RString file);
      FileOutputStream(RString file, vbool append);
      
      virtual void close();
      virtual void flush();
      
      virtual void write(vint byte);
      virtual void write(RArray<vint> bytes);
      virtual void write(RArray<vint> bytes,vint offset,vint num);
   
   private:
      std::wofstream file;
      
      void openFile(RString,vbool);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_FILEOUTPUTSTREAM_H */
