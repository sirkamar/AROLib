#include <aro/core/arm/SyncLock.h>
#include <aro/core/utils/Foreach.h>
#include <aro/core/ThreadException.h>

namespace aro {

SyncLock::SyncLock(const Ref<Object>& obj)
   :subject(obj)
{
   if(subject == nullref)
      ex_throw new ArgumentException("Cannot sync lock null object");
   
   try
   {
      subject->monitor.lock();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

SyncLock::operator bool() const
{
   return true;
}

SyncLock::~SyncLock()
{
   try
   {
      subject->monitor.unlock();
   }
   catch(std::system_error&)
   {
      //ignore error as this may be caused by
      //other exception generated in sync_lock
      //ex_throw new ThreadException(e.what());
   }
}

} /* namespace aro */
