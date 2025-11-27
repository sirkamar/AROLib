#ifndef CORE_RUNNABLE_H
#define CORE_RUNNABLE_H

#include <aro/core/Interface.hpp>

namespace aro {

interface Runnable;
typedef Ref<Runnable> RRunnable;

interface Runnable extends Interface
{
   virtual void run()=0;
};

} /* namespace aro */

#endif /* CORE_RUNNABLE_H */
