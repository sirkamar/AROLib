#ifndef CORE_INT_H
#define CORE_INT_H

#include <aro/core/Number.h>

namespace aro {

class Int;
typedef Ref<Int> RInt;

class Int final : public Number, public Comparable<Int>, public Cloneable<Int>, public io::Streamable<Int>
{
   public:
      static const vint MAX_VALUE;
      static const vint MIN_VALUE;
      
      Int();
      Int(vint val);
      Int(RInt num);
      
	   virtual vint hashCode();
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vint compareTo(RInt val);
      virtual vbool equals(RObject obj);
      
      static vint urShift(vint val, vint n);
      
      static RInt valueOf(RString str);
      static vint parse(RString str);
      static RInt valueOf(vint val);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      const vint value;
};

} /* namespace aro */

#endif /* CORE_INT_H */
