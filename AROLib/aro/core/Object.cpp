#include <aro/core/utils/Foreach.h>
#include <aro/core/ThreadException.h>
#include <aro/core/UnsupportedException.h>

namespace aro {

using namespace std;

Object::Object()
{
   
}

Object::~Object()
{
   
}

RObject Object::clone()
{
   vint typeId = getType()->hashCode();
   
   RObject obj = ObjectFactory::cloneObject(typeId, this);
   
   if(obj == nullref)
      ex_throw new UnsupportedException("Class not cloneable");
   
   return obj;
}

RString Object::getType()
{
	return typeid(*this).name();
}

RString Object::toString()
{
	wstringstream ss;
   
	ss << this;
   
	return getType() + "@" + ss.str().c_str();
}

void Object::wait()
{
   try
   {
	   monitor.wait();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

void Object::notify()
{
   try
   {
      monitor.notify();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

void Object::notifyAll()
{
   try
   {
      monitor.notifyAll();
   }
   catch(std::system_error e)
   {
      ex_throw new ThreadException(e.what());
   }
}

vbool Object::equals(RObject obj)
{
	return obj == thisref;
}

vint Object::hashCode()
{
	wstringstream ss;
   
	ss << this;
   
	return wcstol(ss.str().c_str(), nullptr, 0);
}

void Object::finalize()
{
   
}

void Object::Monitor::lock()
{
   mutex.lock();
}

void Object::Monitor::wait()
{
   cva.wait(mutex);
}

void Object::Monitor::unlock()
{
   mutex.unlock();
}

void Object::Monitor::notify()
{
   cva.notify_one();
}

void Object::Monitor::notifyAll()
{
   cva.notify_all();
}

Object::Monitor& Object::Monitor::operator=(const Object::Monitor&)
{
   return *this;
}

} /* namespace aro */
