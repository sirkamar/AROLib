#ifndef ARO_ARM_ARRAYBASEREF_IMPL_H
#define ARO_ARM_ARRAYBASEREF_IMPL_H

#include <aro/core/arm/RefWeak-impl.hpp>
#include <aro/core/arm/RefArrayBase.hpp>
#include <aro/core/Array.hpp>

namespace aro {

/**********************************************************************
*                     RefArrayBase<T> Implementation                  *
**********************************************************************/
template <class T>
RefArrayBase<T>::RefArrayBase()
{
   
}

template <class T>
RefArrayBase<T>::~RefArrayBase()
{
   
}

template <class T>
typename RefArrayBase<T>::Itr RefArrayBase<T>::end() const
{
   return Itr(*this, size());
}

template <class T>
typename RefArrayBase<T>::Itr RefArrayBase<T>::begin() const
{
   return Itr(*this, 0);
}

template <class T>
const T& RefArrayBase<T>::Itr::operator*() const
{
   return arr[pos];
}

template <class T>
RefArrayBase<T>::Itr::Itr(const RefArrayBase<T>& ra, int p)
   :arr(ra)
{
   pos = p;
}

template <class T>
typename RefArrayBase<T>::Itr& RefArrayBase<T>::Itr::operator++()
{
   if(pos < arr.size())
      pos++;
   
   return *this;
}

template <class T>
bool RefArrayBase<T>::Itr::operator!=(typename const RefArrayBase<T>::Itr& itr) const
{
   return (arr.ptr() != itr.arr.ptr() || pos != itr.pos);
}

} /* namespace aro */

#endif /* ARO_ARM_ARRAYBASEREF_IMPL_H */
