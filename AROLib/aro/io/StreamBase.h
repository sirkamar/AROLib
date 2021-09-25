#ifndef IO_STREAMBASE_H
#define IO_STREAMBASE_H

#include <aro/core/Interface.h>

namespace aro {

namespace io {

template <class T>
interface Streamable;
interface StreamBase;
class ObjectInputStream;
class ObjectOutputStream;

typedef Ref<StreamBase> RStreamBase;
typedef Ref<ObjectInputStream> RObjectInputStream;
typedef Ref<ObjectOutputStream> RObjectOutputStream;

/* A private interface used
 internally by the streaming API.
 Clients should use Streamable<T>. */
interface StreamBase : Interface
{
   protected:
      virtual vlong getObjectVersion()=0;
      
      virtual void readObject(RObjectInputStream is)=0;
      
      virtual void writeObject(RObjectOutputStream os)=0;
   
   private:
      StreamBase() = default;
   
   template <class T>
   friend interface Streamable;
   friend class ObjectInputStream;
   friend class ObjectOutputStream;
};

} /* namespace io */

} /* namespace aro */

#endif /* IO_STREAMBASE_H */
