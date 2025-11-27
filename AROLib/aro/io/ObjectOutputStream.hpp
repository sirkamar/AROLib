#ifndef IO_OBJECTOUTPUTSTREAM_H
#define IO_OBJECTOUTPUTSTREAM_H

#include <aro/io/DataOutputStream.hpp>

namespace aro {

namespace io {

class ObjectOutputStream;
typedef Ref<ObjectOutputStream> RObjectOutputStream;

class ObjectOutputStream extends public DataOutputStream
{
   public:
      ObjectOutputStream(ROutputStream os);
      
      void writeObject(RObject obj);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_OBJECTOUTPUTSTREAM_H */
