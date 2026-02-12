#include <aro/core.hpp>
#include <aro/io/IOException.hpp>
#include <aro/io/ObjectOutputStream.hpp>

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
      
      if(!ObjectFactory::containsFunc<ObjectFactory::newfunc>(typeId))
         ex_throw new IOException("Class not streamable");
      
      RStreamBase rs = type_cast<StreamBase>(obj);
      
      // ouput the type ID for the class
      writeInt(typeId);
      
      // output the class version
      writeLong(rs->getStreamVersionID());
      
      // output the object
      rs->writeObject(thisref);
   }
}

} /* namespace io */

} /* namespace aro */
