#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/DataOutputStream.hpp>

namespace aro {

namespace io {

DataOutputStream::DataOutputStream(ROutputStream os)
   :FilterOutputStream(os)
{
   written = 0;
}

void DataOutputStream::incCount(vint value)
{
   vint temp = written + value;
   
   if(temp < 0)
      temp = Int::MAX_VALUE;
   
   written = temp;
}

vint DataOutputStream::size()
{
   return written;
}

void DataOutputStream::flush()
{
   out->flush();
}

void DataOutputStream::writeInt(vint v)
{
   out->write(Int::urShift(v, 24) & 0xFF);
   out->write(Int::urShift(v, 16) & 0xFF);
   out->write(Int::urShift(v,  8) & 0xFF);
   out->write(Int::urShift(v,  0) & 0xFF);
   incCount(4);
}

void DataOutputStream::writeBool(vbool v)
{
   out->write(v ? 1 : 0);
   incCount(1);
}

void DataOutputStream::writeChar(vchar v)
{
   out->write(Int::urShift(v,  8) & 0xFF);
   out->write(Int::urShift(v,  0) & 0xFF);
   incCount(2);
}

void DataOutputStream::writeLong(vlong v)
{
   //RArray<vint> buf = new Array<vint>(8);
   //
   //buf[0] = (int)(Long::urShift(v, 56) & 0xFF);
   //buf[1] = (int)(Long::urShift(v, 48) & 0xFF);
   //buf[2] = (int)(Long::urShift(v, 40) & 0xFF);
   //buf[3] = (int)(Long::urShift(v, 32) & 0xFF);
   //buf[4] = (int)(Long::urShift(v, 24) & 0xFF);
   //buf[5] = (int)(Long::urShift(v, 16) & 0xFF);
   //buf[6] = (int)(Long::urShift(v, 8) & 0xFF);
   //buf[7] = (int)(Long::urShift(v, 0) & 0xFF);
   //
   //out->write(buf,0,8);
   //incCount(8);
   
   vint val1 = Long::urShift(v, 32);
   vint val2 = Long::urShift(v, 0);

   writeInt(val1);
   writeInt(val2);
}

void DataOutputStream::writeFloat(vfloat v)
{
   writeInt(Float::floatToIntBits(v));
}

void DataOutputStream::writeShort(vshort v)
{
   out->write(Int::urShift(v,  8) & 0xFF);
   out->write(Int::urShift(v,  0) & 0xFF);
   incCount(2);
}

void DataOutputStream::writeDouble(vdouble v)
{
   writeLong(Double::doubleToLongBits(v));
}

void DataOutputStream::write(vint b)
{
   sync_lock(thisref)
   {
      out->write(b);
      incCount(1);
   }
}

void DataOutputStream::write(RArray<vint> buf, vint off, vint num)
{
   sync_lock(thisref)
   {
      out->write(buf, off, num);
      incCount(num);
   }
}

} /* namespace io */

} /* namespace aro */
