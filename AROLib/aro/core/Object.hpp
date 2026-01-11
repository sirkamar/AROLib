#ifndef CORE_OBJECT_H
#define CORE_OBJECT_H

#include <aro/core/arm/Base.hpp>
#include <aro/core/utils/ObjectMonitor.hpp>

namespace aro {

/* Class Object is designed to be the root of the
   class hierarchy for all non-interface types
   defined within the Library. As such every
   object-class within the Library is
   inherited from the Object class
   either directly or indirectly. */
class Object extends public virtual Base
{
   public:
      Object() = default;

      virtual vint hashCode();
      
      virtual RObject clone();
      
      virtual void wait() final;

      virtual RString toString();

      virtual void notify() final;

      virtual void notifyAll() final;

      virtual RString getType() final;

      virtual vbool equals(RObject obj);
   
   protected:
      virtual void finalize();
   
   private:
      ObjectMonitor monitor;
   
   friend class SyncLock;
   template <class T>
   friend interface Cloneable;
};

} /* namespace aro */

#endif /* CORE_OBJECT_H */
