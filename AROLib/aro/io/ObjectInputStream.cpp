#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/ObjectInputStream.h>

namespace aro {

extern const int NULLREFID;

namespace io {

ObjectInputStream::ObjectInputStream(RInputStream is)
   :DataInputStream(is)
{
   
}

RObject ObjectInputStream::readObject()
{
   vint typeId = readInt();

   if(typeId == NULLREFID)
      return nullref;
   
   RObject obj = ObjectFactory::createObject(typeId);
   
   if(obj == nullref)
      ex_throw new IOException("Streamable class not found");
   
   RStreamBase rs = type_cast<StreamBase>(obj);
   
   if(rs->getObjectVersion() != readLong())
      ex_throw new IOException("Streamable object version mismatch");
   
   rs->readObject(thisref);
   
   return obj;
}

} /* namespace io */

} /* namespace aro */
