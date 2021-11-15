#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/DataInputStream.hpp>

namespace aro {

namespace io {

DataInputStream::DataInputStream(RInputStream is)
   :FilterInputStream(is)
{
   
}

vint DataInputStream::read()
{
   return in->read();
}

vint DataInputStream::read(RArray<vint> bytes)
{
   return read(bytes, 0, bytes->length);
}

vint DataInputStream::read(RArray<vint> bytes, vint off, vint num)
{
   return in->read(bytes, off, num);
}

void DataInputStream::readFully(RArray<vint> arr)
{
   readFully(arr,0,arr->length);
}

void DataInputStream::readFully(RArray<vint> arr, vint off, vint num)
{
   if(num < 0)
      ex_throw new IndexException();
   
   vint n=0;
   while(n<num)
   {
      vint count = in->read(arr, off+n, num-n);
      if(count < 0)
         ex_throw new IOException("End-Of-File");
      n += count;
   }
}

vint DataInputStream::readInt()
{
   vint ch1 = in->read();
   vint ch2 = in->read();
   vint ch3 = in->read();
   vint ch4 = in->read();
   
   if((ch1|ch2|ch3|ch4) < 0)
      ex_throw new IOException("End-Of-File");
   
   return ((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0));
}

vbool DataInputStream::readBool()
{
   vint ch = in->read();
   
   if(ch < 0)
      ex_throw new IOException("End-Of-File");
   
   return (ch != 0);
}

vchar DataInputStream::readChar()
{
   vint ch1 = in->read();
   vint ch2 = in->read();
   
   if((ch1|ch2) < 0)
      ex_throw new IOException("End-Of-File");
   
   return (vchar)((ch1 << 8) + (ch2 << 0));
}

vlong DataInputStream::readLong()
{
   //RArray<vint> buf = new Array<vint>(8);
   //
   //readFully(buf, 0, 8);
   //
   //return (((vlong)buf[0]) << 56) +
   //       (((vlong)buf[1]) << 48) +
   //       (((vlong)buf[2]) << 40) +
   //       (((vlong)buf[3]) << 32) +
   //       (((vlong)buf[4]) << 24) +
   //       (buf[5] << 16) +
   //       (buf[6] <<  8) +
   //       (buf[7] <<  0);
   
   vint val1 = readInt();
   vint val2 = readInt();

   return (static_cast<vlong>(val1) << 32) + (val2 << 0);
}

vfloat DataInputStream::readFloat()
{
   return Float::intBitsToFloat(readInt());
}

vshort DataInputStream::readShort()
{
   vint ch1 = in->read();
   vint ch2 = in->read();
   
   if((ch1|ch2) < 0)
      ex_throw new IOException("End-Of-File");
   
   return (vshort)((ch1 << 8) + (ch2 << 0));
}

vdouble DataInputStream::readDouble()
{
   return Double::longBitsToDouble(readLong());
}

} /* namespace io */

} /* namespace aro */
