#ifndef CORE_FLOAT_H
#define CORE_FLOAT_H

#include <aro/core/Number.h>

namespace aro {

class Float;
typedef Ref<Float> RFloat;

class Float final : public Number, public Comparable<Float>, public Cloneable<Float>, public io::Streamable<Float>
{
   public:
      Float();
      Float(vfloat val);
      Float(RFloat num);
      
	   virtual vint hashCode();
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RFloat val);
      
      static vfloat intBitsToFloat(vint bits);
      static vint floatToIntBits(vfloat val);

      static RFloat valueOf(RString str); 
      static RFloat valueOf(vfloat val);
      static vfloat parse(RString str);
      
      //static const vfloat POSITIVE_INFINITY;
      //static const vfloat NEGATIVE_INFINITY;
      static const vfloat MAX_EXPONENT;
      static const vfloat MIN_EXPONENT;
      static const vfloat MAX_VALUE;
      static const vfloat MIN_VALUE;
      //static const vfloat NaN;
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      const vfloat value;
};

} /* namespace aro */

#endif /* CORE_FLOAT_H */
