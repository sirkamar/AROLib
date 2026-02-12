#ifndef CORE_INTEGER_H
#define CORE_INTEGER_H

#include <aro/core/Number.hpp>

namespace aro {

class BigInt;
typedef Ref<BigInt> RBigInt;

class BigInt extends public Number implements public Comparable<BigInt>, public io::Streamable<BigInt>
{
   public:
      static const vint INT_MAX_VALUE;
      static const vint INT_MIN_VALUE;
      static const vlong LONG_MAX_VALUE;
      static const vlong LONG_MIN_VALUE;
      
      BigInt();
      BigInt(vint val);
      BigInt(RBigInt val);
      
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RBigInt num);
      
      static RBigInt valueOf(RString str);
      static RBigInt valueOf(vlong val);
      static vint parse(RString str);

      static vint urShift(vint val, vint n);
      static vlong urShift(vlong val, vint n);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      const vint value;
};

} /* namespace aro */

#endif /* CORE_INTEGER_H */
