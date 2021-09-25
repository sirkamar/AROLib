#ifndef CORE_CLASS_H
#define CORE_CLASS_H

#include <aro/core/Object.h>

namespace aro {

template <class T>
interface Cloneable;

namespace io {

template <class T>
interface Streamable;

}

template <class T>
class Class : public Object
{
   public:
      vint getSource();
      
      //RString getName();
      
      //vbool isTypeOf(RObject obj);
      
      static RObject instantiate();
      
      static RObject clone(RObject obj);
   
   private:
      const vint src;
      
      Class(vint src);
      
      void init() const;
   
   friend class Cloneable<T>;
   //friend class ObjectFactory;
   friend class io::Streamable<T>;
};

} /* namespace aro */

#endif // !CORE_CLASS_H

