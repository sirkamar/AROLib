#ifndef CORE_BOOLEAN_H
#define CORE_BOOLEAN_H

#include <aro/core/String.hpp>

namespace aro {

class Boolean;
typedef Ref<Boolean> RBoolean;

class Boolean extends public Object implements public Comparable<Boolean>, public io::Streamable<Boolean>
{
   public:
      Boolean();
      Boolean(vbool b);
      Boolean(RBoolean val);
      
      static const RBoolean IS_TRUE;
      static const RBoolean IS_FALSE;
      
      virtual vbool boolValue();
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RBoolean b);
      
      static RBoolean valueOf(RString str);
      static RBoolean valueOf(vbool b);
      static vbool parse(RString str);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      vbool value;
      
      static vbool toBool(RString str);
};

} /* namespace aro */

#endif /* CORE_BOOLEAN_H */
