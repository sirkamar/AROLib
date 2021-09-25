#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/FileInputStream.h>

namespace aro {

namespace io {

using namespace std;

FileInputStream::FileInputStream(RString filename)
{
   openFile(filename);
}

void FileInputStream::openFile(RString filename)
{
   file.open(static_cast<const vchar*>(filename), ios::in | ios::binary);
   
   if(!file.is_open())
      ex_throw new IOException("File not found: " + filename);
   
   file.seekg(0, ios::beg);
}

vint FileInputStream::read()
{
   if(!file.is_open())
      ex_throw new IOException("Stream is closed");
   
   unsigned int byte = 0;
   
   file.read(reinterpret_cast<vchar*>(&byte), 1);
   
   if(!file)
   {
      if(file.eof())
      {
         file.clear();
         return -1;
      }
      
      ex_throw new IOException("read from file failed");
   }
   
   return byte;
}

vint FileInputStream::read(RArray<vint> bytes)
{
   return read(bytes, 0, bytes->length);
}

vint FileInputStream::read(RArray<vint> bytes, vint off, vint num)
{
   if(!file.is_open())
      ex_throw new IOException("Stream is closed");
   
   if(off < 0 || off > bytes->length || num < 0 ||
      (off+num < bytes->length) || (off+num < 0))
      ex_throw new IndexException();
   
   else if(num == 0)
      return 0;
   
   vint amt = 0;
   
   for(vint n=0; n<num; n++)
   {
      vint byte = -1;
      
      file.read(reinterpret_cast<vchar*>(&byte), 1);
      
      if(!file)
      {
         if(file.eof())
         {
            file.clear();
            
            if(n==0) // nothing was available to read
               return -1;
            else
               return amt;
         }
         
         ex_throw new IOException("read from file failed");
      }
      
      bytes[off+n] = byte;
      
      amt++;
   }
   
   return amt;
}

vlong FileInputStream::skip(vlong n)
{
   if(!file.is_open())
      ex_throw new IOException("Stream is closed");
   
   if(n < 0)
      ex_throw new IOException("negative file skip value");
   
   streamoff pos = file.tellg();
   
   file.seekg(n, ios::cur);
   
   return (file.tellg() - pos);
}

vint FileInputStream::available()
{
   if(!file.is_open())
     ex_throw new IOException("Stream is closed");
   
   streamoff cur = file.tellg();

   file.seekg(0, ios::end);

   vint size = (vint) (file.tellg() - cur);

   file.seekg(cur);

   return size;
}

void FileInputStream::close()
{
   file.close();
}

} /* namespace io */

} /* namespace aro */
