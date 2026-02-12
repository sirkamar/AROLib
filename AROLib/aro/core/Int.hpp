#ifndef CORE_INT_H
#define CORE_INT_H

#include <aro/core/Number.hpp>

namespace aro {

class Int;
typedef Ref<Int> RInt;

class Int final extends public Number implements public Comparable<Int>, public io::Streamable<Int>
{
   public:
      static const vint BYTE_SIZE;
      static const vint MAX_VALUE;
      static const vint MIN_VALUE;
      
      Int(vint val);
	   Int(RString str);
      
      virtual vint intValue();
      virtual vlong longValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual vint hashCode();
      virtual RString toString();
      virtual vint compareTo(RInt val);
      virtual vbool equals(RObject obj);
      
      static vint urShift(vint val, vint n);
      
      static RString toString(vint val, vint radix);
	   static RInt valueOf(RString str, vint radix);
      static vint parse(RString str, vint radix);
      static RString toString(vint val);
      static RInt valueOf(RString str);
      static vint parse(RString str);
      static RInt valueOf(vint val);
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Int(); // required by Streamable
      
      const vint value;

      static const RArray<vchar> digits;
      static const RArray<vchar> digitTens;
      static const RArray<vchar> digitOnes;
      static const RArray<vint> sizeTable;

      static vint stringSize(vint val);
      static vint toDigit(vchar c, vint radix);
      static void getChars(vint val, vint index, RArray<vchar> buf);

      class IntCache final extends public Object
      {
         public:
            IntCache();

            RArray<Int> cache;
            static const vint low;
            static const vint high;
      };

      static const Ref<IntCache> intCache;

   friend class Long;
   friend interface io::Streamable<Int>;
};

} /* namespace aro */

#endif /* CORE_INT_H */
