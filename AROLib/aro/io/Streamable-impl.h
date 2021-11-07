#ifndef IO_STREAMABLE_IMPL_H
#define IO_STREAMABLE_IMPL_H

#include <aro/core/Cloneable-impl.h>

namespace aro {

namespace io {

template <class T>
const aro::Class<T> Streamable<T>::TYPEID = 2;

template <class T>
Streamable<T>::Streamable()
{
	TYPEID.init();
}

template <class T>
vlong Streamable<T>::getObjectVersion()
{
	return 1L;
}

} /* namespace io */

} /* namespace aro */

#endif /* IO_STREAMABLE_IMPL_H */
