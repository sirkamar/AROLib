#ifndef ARO_ARM_SYNCLOCK_H
#define ARO_ARM_SYNCLOCK_H

#include <aro/core/arm/RefString.h>

namespace aro {

/* Used to create a mutex-based
synchronized block for managing
multi-threading access */
class SyncLock
{
   public:
      ~SyncLock();
      
      operator bool() const;
      
      SyncLock(const Ref<Object>& o);
   
   private:
      const Ref<Object> subject;
};

} /* namespace aro */

#endif /* ARO_ARM_SYNCLOCK_H */
