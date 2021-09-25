#ifndef IO_OBJECTOUTPUTSTREAM_H
#define IO_OBJECTOUTPUTSTREAM_H

#include <aro/io/DataOutputStream.h>

namespace aro {

namespace io {

class ObjectOutputStream;
typedef Ref<ObjectOutputStream> RObjectOutputStream;

class ObjectOutputStream : public DataOutputStream
{
   public:
      ObjectOutputStream(ROutputStream os);
      
      void writeObject(RObject obj);
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_OBJECTOUTPUTSTREAM_H */
