#ifndef CORE_DOUBLE_H
#define CORE_DOUBLE_H

#include <aro/core/Number.hpp>

namespace aro {

class Double;
typedef Ref<Double> RDouble;

class Double final : public Number, public Comparable<Double>, public Cloneable<Double>, public io::Streamable<Double>
{
   public:
      /*static const vdouble POSITIVE_INFINITY;
      static const vdouble NEGATIVE_INFINITY;*/
      static const vdouble MAX_EXPONENT;
      static const vdouble MIN_EXPONENT;
      static const vdouble MAX_VALUE;
      static const vdouble MIN_VALUE;
      /*static const vdouble NaN;*/
      
      Double();
      Double(vdouble val);
      Double(RDouble num);
      
	   virtual vint hashCode();
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RDouble val);
      
      static vdouble longBitsToDouble(vlong bits);
      static vlong doubleToLongBits(vdouble val);

      static RDouble valueOf(RString val); 
      static RDouble valueOf(vdouble val);
      static vdouble parse(RString val);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      const vdouble value;
};

} /* namespace aro */

#endif /* CORE_DOUBLE_H */
