#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/ObjectOutputStream.h>

namespace aro {

namespace io {

ObjectOutputStream::ObjectOutputStream(ROutputStream os)
   :DataOutputStream(os)
{
   
}

void ObjectOutputStream::writeObject(RObject obj)
{
   static const int NULLID = RString("aro::Null")->hashCode();

   if(obj == nullref)
      writeInt(NULLID);
   else
   {
      int typeId = obj->getType()->hashCode();
      
      if(!ObjectFactory::containsNewFunc(typeId) || !type_of<StreamBase>(obj))
         ex_throw new IOException("writeObject requires a Streamable object");
      
      RStreamBase rs = type_cast<StreamBase>(obj);
      
      // ouput the type ID for the class
      writeInt(typeId);
      
      // output the class version
      writeLong(rs->getObjectVersion());
      
      // output the object
      rs->writeObject(thisref);
   }
}

} /* namespace io */

} /* namespace aro */
