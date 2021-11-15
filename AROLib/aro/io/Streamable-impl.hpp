#ifndef IO_STREAMABLE_IMPL_H
#define IO_STREAMABLE_IMPL_H

#include <aro/core/Cloneable-impl.hpp>

namespace aro {

namespace io {

template <class T>
const typename Streamable<T>::Builder Streamable<T>::BUILDER;

template <class T>
Streamable<T>::Streamable()
{
	BUILDER.init();
}

template <class T>
vlong Streamable<T>::getObjectVersion()
{
	return 1L;
}

template <class T>
Streamable<T>::Builder::Builder()
{
	RString name = typeid(T).name();

	vint type = name->hashCode();

	ObjectFactory::add(type, create);
}

template <class T>
void Streamable<T>::Builder::init() const
{
   // do nothing
}

template <class T>
RObject Streamable<T>::Builder::create()
{
	return new T();
}

} /* namespace io */

} /* namespace aro */

#endif /* IO_STREAMABLE_IMPL_H */
