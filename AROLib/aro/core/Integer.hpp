#ifndef CORE_INTEGER_H
#define CORE_INTEGER_H

#include <aro/core/Number.hpp>

// TODO: convert to BigInteger

namespace aro {

class Integer;
typedef Ref<Integer> RInteger;

class Integer extends public Number implements public Comparable<Integer>, public io::Streamable<Integer>
{
   public:
      static const vint INT_MAX_VALUE;
      static const vint INT_MIN_VALUE;
      static const vlong LONG_MAX_VALUE;
      static const vlong LONG_MIN_VALUE;
      
      Integer();
      Integer(vint val);
      Integer(RInteger val);
      
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RInteger num);
      
      static RInteger valueOf(RString str);
      static RInteger valueOf(vlong val);
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
