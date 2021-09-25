#ifndef CORE_LONG_H
#define CORE_LONG_H

#include <aro/core/Number.h>

namespace aro {

class Long;
typedef Ref<Long> RLong;

class Long final : public Number, public Comparable<Long>, public Cloneable<Long>, public io::Streamable<Long>
{
   public:
      static const vlong MAX_VALUE;
      static const vlong MIN_VALUE;
      
      Long();
      Long(vlong val);
      Long(RLong num);
      
	   virtual vint hashCode();
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vint compareTo(RLong val);
      virtual vbool equals(RObject obj);
      
      static RLong valueOf(RString str);
      static RLong valueOf(vlong val);
      static vlong parse(RString str);
      
      static vlong urShift(vlong val, vint n);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      const vlong value;
};

} /* namespace aro */

#endif /* CORE_LONG_H */
