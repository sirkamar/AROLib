#ifndef CORE_BOOL_H
#define CORE_BOOL_H

#include <aro/core/String.hpp>

namespace aro {

class Bool;
typedef Ref<Bool> RBool;

class Bool final extends public Object implements public Comparable<Bool>, public io::Streamable<Bool>
{
   public:
      static const RBool FALSE_REF;
      static const RBool TRUE_REF;
      
      Bool(vbool b);
	  Bool(RString s);
      
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
      Bool();
      
      const vbool value;
      
      static vbool toBool(RString str);
   
   friend interface io::Streamable<Bool>;
};

} /* namespace aro */

#endif /* CORE_BOOL_H */
