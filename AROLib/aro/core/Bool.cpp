#include <aro/core/Bool.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

const vint Bool::BYTE_SIZE = 1; // 1 byte = 8 bits; technically only 1 bit needed

const RBool Bool::TRUE_REF = new Bool(true);

const RBool Bool::FALSE_REF = new Bool(false);

Bool::Bool()
   :Bool(false)
{
   
}

Bool::Bool(vbool val)
   :value(val)
{
   
}

Bool::Bool(RString str)
    :Bool(toBool(str))
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
   return (str != nullref && str->equalsIgnoreCase("true"));
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
   return b ? TRUE_REF : FALSE_REF;
}

RBool Bool::valueOf(RString str)
{
   return toBool(str) ? TRUE_REF : FALSE_REF;
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
