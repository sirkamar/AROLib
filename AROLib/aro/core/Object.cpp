#include <aro/core/impl/All.hpp>
#include <aro/core/ThreadException.hpp>
#include <aro/core/UnsupportedException.hpp>

namespace aro {

using namespace std;

RObject Object::clone()
{
   RObject obj = ObjectFactory::cloneObject(thisref);
   
   if(obj == nullref)
      ex_throw new UnsupportedException("Class not cloneable: " + getType());
   
   return obj;
}

RString Object::getType()
{
	RString type = typeid(*this).name();

	vint pos = type->lastIndexOf(' ');

	if(pos >= 0)
		return type->substring(pos+1);

	return type;
}

RString Object::toString()
{
	wstringstream ss;
   
	ss << this;
   
	return getType() + "@" + ss.str().c_str();
}

void Object::wait()
{
   monitor.wait();
}

void Object::notify()
{
   monitor.notify();
}

void Object::notifyAll()
{
   monitor.notifyAll();
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
   // default implementation does nothing
}

} /* namespace aro */
