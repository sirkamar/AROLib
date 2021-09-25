#ifndef CORE_DECIMAL_H
#define CORE_DECIMAL_H

#include <aro/core/Number.h>

namespace aro {

class Decimal;
typedef Ref<Decimal> RDecimal;

class Decimal : public Number, public Comparable<Decimal>, public Cloneable<Decimal>, public io::Streamable<Decimal>
{
   public:
      //static const vdouble POSITIVE_INFINITY;
      //static const vdouble NEGATIVE_INFINITY;
      static const vdouble MAX_EXPONENT;
      static const vdouble MIN_EXPONENT;
      static const vdouble MAX_VALUE;
      static const vdouble MIN_VALUE;
      //static const vdouble NaN;
      
      Decimal();
      Decimal(vdouble val);
      Decimal(RDecimal val);
      
      vint intValue();
      vlong longValue();
      vfloat floatValue();
      vdouble doubleValue();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RDecimal obj);
      
      static vdouble longBitsToDouble(vlong bits);
      static vlong doubleToLongBits(vdouble val);
      static vfloat intBitsToFloat(vint bits);
      static vint floatToIntBits(vfloat val);
      
      static RDecimal valueOf(RString val); 
      static RDecimal valueOf(vdouble val);
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
