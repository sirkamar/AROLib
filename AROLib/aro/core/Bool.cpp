#include <aro/core/Bool.h>
#include <aro/core/utils/Foreach.h>

namespace aro {

const RBool Bool::IS_FALSE = new Bool(false);

const RBool Bool::IS_TRUE = new Bool(true);

Bool::Bool()
   :value(false)
{
   
}

Bool::Bool(vbool val)
   :value(val)
{
   
}

Bool::Bool(RBool val)
   :value(val->value)
{
   
}

vint Bool::hashCode()
{
   return value ? 1231 : 1237;
}

vbool Bool::boolValue()
{
   return value;
}

vbool Bool::parse(RString str)
{
   return toBool(str);
}

vbool Bool::toBool(RString str)
{
   return str->equalsIgnoreCase("true");
}

RString Bool::toString()
{
   return String::valueOf(value);
}

void Bool::readObject(io::RObjectInputStream is)
{
   //TODO: solving reading from stream to const item
   const_cast<vbool&>(value) = is->readBool();
}

void Bool::writeObject(io::RObjectOutputStream os)
{
   os->writeBool(value);
}

RBool Bool::valueOf(vbool b)
{
   return b ? IS_TRUE : IS_FALSE;
}

RBool Bool::valueOf(RString str)
{
   return toBool(str) ? IS_TRUE : IS_FALSE;
}

vint Bool::compareTo(RBool b)
{
   return (value == b->value ? 0 : (value ? 1 : -1));
}

vbool Bool::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Bool>(obj))
   {
      RBool val = type_cast<Bool>(obj);
      
      return value == val->value;
   }
   
   return false;
}

} /* namespace aro */
