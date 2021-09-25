#ifndef CORE_OBJECT_H
#define CORE_OBJECT_H

#include <aro/core/Base.h>

namespace aro {

/* Class Object is designed to be the root of the
   class hierarchy for all non-interface classes
   defined within the Library. As such every
   non-abstract class within the Library
   is inherited from the Object class
   either directly or indirectly. */
class Object : public virtual Base
{
   public:
      Object();
	  
      virtual ~Object();

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
      struct Monitor
      {
         void wait();
         
         void lock();
         
         void unlock();
         
         void notify();
         
         void notifyAll();
         
         /** Used to implement exclusion */
         std::recursive_mutex mutex;
         
         /** Used to implement wait/notify */
         std::condition_variable_any cva;

         Monitor& operator=(const Monitor&);
      } monitor;
   
   friend class SyncLock;
};

} /* namespace aro */

#endif /* CORE_OBJECT_H */
