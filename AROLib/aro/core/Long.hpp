#ifndef CORE_LONG_H
#define CORE_LONG_H

#include <aro/core/Number.hpp>

namespace aro {

class Long;
typedef Ref<Long> RLong;

class Long final extends public Number implements public Comparable<Long>, public io::Streamable<Long>
{
   public:
      static const vint BYTE_SIZE;
      static const vlong MAX_VALUE;
      static const vlong MIN_VALUE;
      
      Long(vlong val);
	  Long(RString str);
      
	  virtual vint hashCode();
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual RString toString();
      virtual vint compareTo(RLong val);
      virtual vbool equals(RObject obj);
      
      static vlong urShift(vlong val, vint n);

      static RString toString(vlong val, vint radix);
      static RLong valueOf(RString str, vint radix);
      static vlong parse(RString str, vint radix);
      static RString toString(vlong val);
      static RLong valueOf(RString str);
      static vlong parse(RString str);
      static RLong valueOf(vlong val);

   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Long(); // required by Streamable
      
      const vlong value;
      
      static vint stringSize(vlong val);
      static void getChars(vlong i, vint index, RArray<vchar> buf);
      
      class LongCache final extends public Object
      {
         public:
            LongCache();
            
            RArray<Long> cache;
      };
      
      static const Ref<LongCache> longCache;

   friend interface io::Streamable<Long>;
};

} /* namespace aro */

#endif /* CORE_LONG_H */
