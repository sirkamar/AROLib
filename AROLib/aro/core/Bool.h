#ifndef CORE_BOOL_H
#define CORE_BOOL_H

#include <aro/core/String.h>

namespace aro {

class Bool;
typedef Ref<Bool> RBool;

class Bool final : public Object, public Comparable<Bool>, public io::Streamable<Bool>
{
   public:
      static const RBool IS_FALSE;
      static const RBool IS_TRUE;
      
      Bool();
      Bool(vbool b);
      Bool(RBool b);
      
	   virtual vint hashCode();
      virtual vbool boolValue();
      virtual RString toString();
      virtual vint compareTo(RBool b);
      virtual vbool equals(RObject obj);
      
      static RBool valueOf(RString str);
      static vbool parse(RString str);
      static RBool valueOf(vbool b);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      const vbool value;
      
      static vbool toBool(RString str);
};

} /* namespace aro */

#endif /* CORE_BOOL_H */
