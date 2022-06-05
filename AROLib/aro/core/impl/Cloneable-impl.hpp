#ifndef CORE_CLONEABLE_IMPL_H
#define CORE_CLONEABLE_IMPL_H

#include <aro/core/impl/Weak-impl.hpp>
#include <aro/core/utils/ObjectFactory-impl.hpp>

namespace aro {

template <class T>
const typename Cloneable<T>::Builder Cloneable<T>::BUILDER;

template <class T>
Cloneable<T>::Cloneable()
{
	BUILDER.init();
}

template <class T>
Cloneable<T>::Builder::Builder()
{
	RString name = typeid(T).name();

	vint type = name->hashCode();

	ObjectFactory::add(type, clone);
}

template <class T>
void Cloneable<T>::Builder::init() const
{
	// do nothing
}

template <class T>
RObject Cloneable<T>::Builder::clone(RObject obj)
{
	Ref<T> o_tmp = type_cast<T>(obj);

    return new T((*o_tmp.operator->()));
}

} /* namespace aro */

#endif /* CORE_CLONEABLE_IMPL_H */
