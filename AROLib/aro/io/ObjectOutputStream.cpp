#include <aro/core.h>
#include <aro/io/IOException.h>
#include <aro/io/ObjectOutputStream.h>

namespace aro {

namespace io {

const int NULLREFID = RString("aro::Null")->hashCode();

ObjectOutputStream::ObjectOutputStream(ROutputStream os)
   :DataOutputStream(os)
{
   
}

void ObjectOutputStream::writeObject(RObject obj)
{
   if(obj == nullref)
      writeInt(NULLREFID);
   else
   {
      vint typeId = obj->getType()->hashCode();
      
      if(!type_of<StreamBase>(obj))
         ex_throw new IOException("Class of object not Streamable");
      
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
