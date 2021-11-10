#ifndef CORE_CLONEABLE_IMPL_H
#define CORE_CLONEABLE_IMPL_H

#include <aro/core/Weak-impl.h>
#include <aro/core/utils/ObjectFactory.h>

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
	Ref<T> tmp = new T();

	Ref<T> o_tmp = type_cast<T>(obj);

	(*tmp.operator->()) = (*o_tmp.operator->());

	return tmp;
}

} /* namespace aro */

#endif /* CORE_CLONEABLE_IMPL_H */
