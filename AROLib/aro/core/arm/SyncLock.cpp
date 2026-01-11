#include <aro/core/arm/SyncLock.hpp>
#include <aro/core/utils/Foreach.hpp>
#include <aro/core/ThreadException.hpp>

namespace aro {

SyncLock::SyncLock(const Ref<Object>& obj)
   :subject(obj)
{
   if(subject == nullref)
      ex_throw new ArgumentException("Cannot sync_lock null object");
   
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
