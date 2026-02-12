#ifndef CORE_DECIMAL_H
#define CORE_DECIMAL_H

#include <aro/core/Number.hpp>

namespace aro {

class BigFloat;
typedef Ref<BigFloat> RBigFloat;

class BigFloat extends public Number implements public Comparable<BigFloat>, public io::Streamable<BigFloat>
{
   public:
      //static const vdouble POSITIVE_INFINITY;
      //static const vdouble NEGATIVE_INFINITY;
      static const vdouble MAX_EXPONENT;
      static const vdouble MIN_EXPONENT;
      static const vdouble MAX_VALUE;
      static const vdouble MIN_VALUE;
      //static const vdouble NaN;
      
      BigFloat();
      BigFloat(vdouble val);
      BigFloat(RBigFloat val);
      
      vint intValue();
      vlong longValue();
      vfloat floatValue();
      vdouble doubleValue();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RBigFloat obj);
      
      static vdouble longBitsToDouble(vlong bits);
      static vlong doubleToLongBits(vdouble val);
      static vfloat intBitsToFloat(vint bits);
      static vint floatToIntBits(vfloat val);
      
      static RBigFloat valueOf(RString val); 
      static RBigFloat valueOf(vdouble val);
      static vdouble parse(RString val);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      //vint sign;
      //vbool* bits;
      vdouble value;
};

} /* namespace aro */

#endif /* CORE_DECIMAL_H */
