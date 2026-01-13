#include <aro/core/impl/All.hpp>
#include <aro/core/ThreadException.hpp>
#include <aro/core/utils/ObjectMonitor.hpp>

namespace aro {

void ObjectMonitor::lock()
{
   try
   {
	  mutex.lock();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

void ObjectMonitor::wait()
{
   try
   {
	  cva.wait(mutex);
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

void ObjectMonitor::unlock()
{
   try
   {
	  mutex.unlock();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

void ObjectMonitor::notify()
{
   try
   {
	  cva.notify_one();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

void ObjectMonitor::notifyAll()
{
   try
   {
      cva.notify_all();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

ObjectMonitor::ObjectMonitor(const ObjectMonitor&)
{
   // copy constructor does nothing (allows Object::clone to compile)
}

ObjectMonitor& ObjectMonitor::operator=(const ObjectMonitor&)
{
   // assignment operator does nothing (allows Object::clone to compile)
   return *this;
}

} /* namespace aro */
