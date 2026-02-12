#ifndef CORE_SHORT_H
#define CORE_SHORT_H

#include <aro/core/Number.hpp>

namespace aro {

class Short;
typedef Ref<Short> RShort;

class Short final extends public Number implements public Comparable<Short>, public io::Streamable<Short>
{
   public:
      Short(vshort val);
	  Short(RString str);
      
      virtual vint intValue();
      virtual vlong longValue();
	  virtual vshort shortValue();
      virtual vfloat floatValue();
      virtual vdouble doubleValue();
      
      virtual vint hashCode();
	  virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual vint compareTo(RShort val);
      
      static RString toString(vshort val, vint radix);
      static RShort valueOf(RString str, vint radix);
      static vshort parse(RString str, vint radix);
      static RString toString(vshort val);
      static RShort valueOf(RString str);
      static RShort valueOf(vshort num);
      static vshort parse(RString str);
      
      static const vshort MAX_VALUE;
      static const vshort MIN_VALUE;
   
   protected:
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   private:
      Short(); // required by Streamable
      
      const vshort value;

      class ShortCache final extends public Object
      {
         public:
            ShortCache();

            RArray<Short> cache;
      };

      static const Ref<ShortCache> shortCache;

   friend interface io::Streamable<Short>;
};

} /* namespace aro */

#endif /*CORE_SHORT_H*/
