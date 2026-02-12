#ifndef ARO_ARM_ARRAYBASEREF_IMPL_H
#define ARO_ARM_ARRAYBASEREF_IMPL_H

#include <aro/core/arm/RefWeak-impl.hpp>
#include <aro/core/arm/RefArrayBase.hpp>
#include <aro/core/Array.hpp>

namespace aro {

/**********************************************************************
*                     RefArrayBase<T> Implementation                  *
**********************************************************************/
template <class T, class V>
RefArrayBase<T,V>::RefArrayBase()
{
   ref = nullptr;
}

template <class T, class V>
RefArrayBase<T,V>::~RefArrayBase()
{
   
}

template <class T, class V>
typename RefArrayBase<T,V>::Itr RefArrayBase<T,V>::end() const
{
   return Itr(*this, size());
}

template <class T, class V>
typename RefArrayBase<T,V>::Itr RefArrayBase<T,V>::begin() const
{
   return Itr(*this, 0);
}

template <class T, class V>
typename Array<T>* RefArrayBase<T,V>::operator->() const
{
   if(ref == nullptr)
      throw RException(new NullException());
   
   return ref;
}

template <class T, class V>
const V& RefArrayBase<T,V>::Itr::operator*() const
{
   return arr[pos];
}

template <class T, class V>
RefArrayBase<T,V>::Itr::Itr(const RefArrayBase<T,V>& ra, int p)
   :arr(ra)
{
   pos = p;
}

template <class T, class V>
typename RefArrayBase<T,V>::Itr& RefArrayBase<T,V>::Itr::operator++()
{
   if(pos < arr.size())
      pos++;
   
   return *this;
}

template <class T, class V>
bool RefArrayBase<T,V>::Itr::operator!=(typename const RefArrayBase<T,V>::Itr& itr) const
{
   return (arr.ptr() != itr.arr.ptr() || pos != itr.pos);
}

} /* namespace aro */

#endif /* ARO_ARM_ARRAYBASEREF_IMPL_H */
