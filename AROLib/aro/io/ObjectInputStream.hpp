#ifndef IO_OBJECTINPUTSTREAM_H
#define IO_OBJECTINPUTSTREAM_H

#include <aro/io/DataInputStream.hpp>

namespace aro {

namespace io {

class ObjectInputStream;
typedef Ref<ObjectInputStream> RObjectInputStream;

class ObjectInputStream : public DataInputStream
{
   public:
     ObjectInputStream(RInputStream is);
     
     virtual RObject readObject();
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_OBJECTINPUTSTREAM_H */
