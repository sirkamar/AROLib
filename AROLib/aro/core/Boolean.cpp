#include <aro/core/Boolean.h>
#include <aro/core/utils/Foreach.h>

namespace aro {

const RBoolean Boolean::IS_TRUE = new Boolean(true);

const RBoolean Boolean::IS_FALSE = new Boolean(false);

vbool Boolean::boolValue()
{
   return value;
}

Boolean::Boolean()
{
   value = false;
}

Boolean::Boolean(vbool b)
{
   value = b;
}

Boolean::Boolean(RBoolean val)
{
   value = val->value;
}

RString Boolean::toString()
{
   return String::valueOf(value);
}

vbool Boolean::parse(RString str)
{
   return toBool(str);
}

vbool Boolean::toBool(RString str)
{
   return (str != nullref && str->equalsIgnoreCase("true"));
}

RBoolean Boolean::valueOf(vbool b)
{
   return b ? IS_TRUE : IS_FALSE;
}

void Boolean::readObject(io::RObjectInputStream is)
{
   value = is->readBool();
}

void Boolean::writeObject(io::RObjectOutputStream os)
{
   os->writeBool(value);
}

RBoolean Boolean::valueOf(RString str)
{
   return toBool(str) ? IS_TRUE : IS_FALSE;
}

vint Boolean::compareTo(RBoolean b)
{
   return (value == b->value ? 0 : (value ? 1 : -1));
}

vbool Boolean::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Boolean>(obj))
   {
      RBoolean val = type_cast<Boolean>(obj);
      
      return value == val->value;
   }
   
   return false;
}

} /* namespace aro */
