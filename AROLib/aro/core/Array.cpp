#include <aro/core/utils/Foreach.hpp>

namespace aro {

//template <>
Array<vint>::Array()
   :Array<vint>(0)
{
   
}

//template <>
Array<vint>::Array(vint size)
   :ArrayBase<vint>(size)
{
   
}

//template <>
Array<vint>::Array(RArray<vint> arr)
   :ArrayBase<vint>(arr)
{
   
}

//template <>
Array<vint>::Array(std::initializer_list<vint> elems)
   :ArrayBase<vint>(elems)
{
   
}

//template <>
RArray<vint> Array<vint>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vint> Array<vint>::copyOf(vint offset, vint count)
{
   RArray<vint> arr = new Array<vint>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vint>::copy(vint dPos, RArray<vint> src, vint sPos, vint num)
{
   ArrayBase<vint>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vint>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vint>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readInt();
}

//template<>
void Array<vint>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);

   for(vint n = 0; n<length; n++)
      os->writeInt(item(n));
}



//template <>
Array<vbool>::Array()
   :Array<vbool>(0)
{

}

//template <>
Array<vbool>::Array(vint size)
   :ArrayBase<vbool>(size)
{
   
}

//template <>
Array<vbool>::Array(RArray<vbool> arr)
   :ArrayBase<vbool>(arr)
{
   
}

//template <>
Array<vbool>::Array(std::initializer_list<vbool> elems)
   :ArrayBase<vbool>(elems)
{
   
}

//template <>
RArray<vbool> Array<vbool>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vbool> Array<vbool>::copyOf(vint offset, vint count)
{
   RArray<vbool> arr = new Array<vbool>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vbool>::copy(vint dPos, RArray<vbool> src, vint sPos, vint num)
{
   ArrayBase<vbool>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vbool>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vbool>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readBool();
}

//template<>
void Array<vbool>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);

   for(vint n = 0; n<length; n++)
      os->writeBool(item(n));
}


//template <>
Array<vchar>::Array()
   :Array<vchar>(0)
{

}

//template <>
Array<vchar>::Array(vint size)
   :ArrayBase<vchar>(size)
{
   
}

//template <>
Array<vchar>::Array(RArray<vchar> arr)
   :ArrayBase<vchar>(arr)
{
   
}

//template <>
Array<vchar>::Array(std::initializer_list<vchar> elems)
   :ArrayBase<vchar>(elems)
{
   
}

//template <>
RArray<vchar> Array<vchar>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vchar> Array<vchar>::copyOf(vint offset, vint count)
{
   RArray<vchar> arr = new Array<vchar>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vchar>::copy(vint dPos, RArray<vchar> src, vint sPos, vint num)
{
   ArrayBase<vchar>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vchar>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vchar>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readChar();
}

//template<>
void Array<vchar>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);

   for(vint n = 0; n<length; n++)
      os->writeChar(item(n));
}


//template <>
Array<vlong>::Array()
   :Array<vlong>(0)
{

}

//template <>
Array<vlong>::Array(vint size)
   :ArrayBase<vlong>(size)
{
   
}

//template <>
Array<vlong>::Array(RArray<vlong> arr)
   :ArrayBase<vlong>(arr)
{
   
}

//template <>
Array<vlong>::Array(std::initializer_list<vlong> elems)
   :ArrayBase<vlong>(elems)
{
   
}

//template <>
RArray<vlong> Array<vlong>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vlong> Array<vlong>::copyOf(vint offset, vint count)
{
   RArray<vlong> arr = new Array<vlong>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vlong>::copy(vint dPos, RArray<vlong> src, vint sPos, vint num)
{
   ArrayBase<vlong>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vlong>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vlong>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readLong();
}

//template<>
void Array<vlong>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);

   for(vint n = 0; n<length; n++)
      os->writeLong(item(n));
}


//template <>
Array<vshort>::Array()
   :Array<vshort>(0)
{

}

//template <>
Array<vshort>::Array(vint size)
   :ArrayBase<vshort>(size)
{
   
}

//template <>
Array<vshort>::Array(RArray<vshort> arr)
   :ArrayBase<vshort>(arr)
{
   
}

//template <>
Array<vshort>::Array(std::initializer_list<vshort> elems)
   :ArrayBase<vshort>(elems)
{
   
}

//template <>
RArray<vshort> Array<vshort>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vshort> Array<vshort>::copyOf(vint offset, vint count)
{
   RArray<vshort> arr = new Array<vshort>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vshort>::copy(vint dPos, RArray<vshort> src, vint sPos, vint num)
{
   ArrayBase<vshort>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vshort>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vshort>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readShort();
}

//template<>
void Array<vshort>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);

   for(vint n = 0; n<length; n++)
      os->writeShort(item(n));
}


//template <>
Array<vfloat>::Array()
   :Array<vfloat>(0)
{

}

//template <>
Array<vfloat>::Array(vint size)
   :ArrayBase<vfloat>(size)
{
   
}

//template <>
Array<vfloat>::Array(RArray<vfloat> arr)
   :ArrayBase<vfloat>(arr)
{
   
}

//template <>
Array<vfloat>::Array(std::initializer_list<vfloat> elems)
   :ArrayBase<vfloat>(elems)
{
   
}

//template <>
RArray<vfloat> Array<vfloat>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vfloat> Array<vfloat>::copyOf(vint offset, vint count)
{
   RArray<vfloat> arr = new Array<vfloat>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vfloat>::copy(vint dPos, RArray<vfloat> src, vint sPos, vint num)
{
   ArrayBase<vfloat>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vfloat>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vfloat>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readFloat();
}

//template<>
void Array<vfloat>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);
   
   for(vint n = 0; n<length; n++)
      os->writeFloat(item(n));
}


//template <>
Array<vdouble>::Array()
   :Array<vdouble>(0)
{

}

//template <>
Array<vdouble>::Array(vint size)
   :ArrayBase<vdouble>(size)
{
   
}

//template <>
Array<vdouble>::Array(RArray<vdouble> arr)
   :ArrayBase<vdouble>(arr)
{
   
}

//template <>
Array<vdouble>::Array(std::initializer_list<vdouble> elems)
   :ArrayBase<vdouble>(elems)
{
   
}

//template <>
RArray<vdouble> Array<vdouble>::copyOf(vint count)
{
   return copyOf(0, count);
}

//template <>
RArray<vdouble> Array<vdouble>::copyOf(vint offset, vint count)
{
   RArray<vdouble> arr = new Array<vdouble>(count);
   
   arr->copy(0, thisref, offset, Math::minimum(length, count));
   
   return arr;
}

//template<>
void Array<vdouble>::copy(vint dPos, RArray<vdouble> src, vint sPos, vint num)
{
   ArrayBase<vdouble>::copyItems(dPos, src, sPos, num);
}

//template<>
void Array<vdouble>::readObject(io::RObjectInputStream is)
{
   ArrayBase<vdouble>::resize(is->readInt());
   
   for(vint n=0; n<length; n++)
      item(n) = is->readDouble();
}

//template<>
void Array<vdouble>::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(length);

   for(vint n = 0; n<length; n++)
      os->writeDouble(item(n));
}

} /* namespace aro */
