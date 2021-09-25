#ifndef IO_STREAMABLE_IMP_H
#define IO_STREAMABLE_IMP_H

#include <aro/core/Cloneable_.h>

namespace aro {

namespace io {

template <class T>
const aro::Class<T> Streamable<T>::STREAMID = 2;

template <class T>
Streamable<T>::Streamable()
{
	STREAMID.init();
}

template <class T>
vlong Streamable<T>::getObjectVersion()
{
	return 1L;
}

} /* namespace io */

} /* namespace aro */

#endif /* IO_STREAMABLE_IMP_H */
