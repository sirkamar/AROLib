#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/FileOutputStream.h>

namespace aro {

namespace io {

using namespace std;

FileOutputStream::FileOutputStream(RString filename)
{
   openFile(filename, false);
}

FileOutputStream::FileOutputStream(RString filename, vbool append)
{
   openFile(filename, append);
}

void FileOutputStream::openFile(RString filename, vbool append)
{
   vint mode = append ? ios::binary | ios::out | ios::ate : ios::binary | ios::out;

   file.open(static_cast<const vchar*>(filename), mode);
   
   if(!file.is_open())
      ex_throw new IOException("File not found: " + filename);
   
   file.seekp(0, append ? ios::end : ios::beg);
}

void FileOutputStream::write(vint byte)
{
   if(!file.is_open())
      ex_throw new IOException("Stream is closed");
   
   unsigned int uByte = byte;
   
   file.write(reinterpret_cast<const vchar*>(&uByte), 1);
   
   if(!file)
      ex_throw new IOException("write to file failed");
}

void FileOutputStream::write(RArray<vint> bytes)
{
   write(bytes, 0, bytes->length);
}

void FileOutputStream::write(RArray<vint> bytes, vint off, vint num)
{
   if(!file.is_open())
      ex_throw new IOException("Stream is closed");
   
   if(off < 0 || off > bytes->length || num < 0 ||
      (off+num < bytes->length) || (off+num < 0))
      ex_throw new IndexException();
   
   else if(num == 0)
      return;
   
   for(vint n=0; n<bytes->length; n++)
   {
      file.write(reinterpret_cast<const vchar*>(&bytes[n]), 1);
      
      if(!file)
         ex_throw new IOException("write to file failed");
   }
}

void FileOutputStream::flush()
{
   if(!file.is_open())
      ex_throw new IOException("Stream is closed");
   
   file.flush();
}

void FileOutputStream::close()
{
   file.close();
}

} /* namespace io */

} /* namespace aro */
