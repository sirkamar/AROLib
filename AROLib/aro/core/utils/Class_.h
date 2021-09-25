#ifndef CORE_CLASS_IMP_H
#define CORE_CLASS_IMP_H

#include <aro/core/Weak_.h>
//#include <aro/core/utils/Class.h>
#include <aro/core/utils/ObjectFactory.h>

namespace aro {

template <class T>
Class<T>::Class(vint source)
   :src(source)
{
   RString type = typeid(T).name();
   
   if(src == 1)
      ObjectFactory::add(type->hashCode(), clone);
   else
      ObjectFactory::add(type->hashCode(), instantiate);
}

template <class T>
void Class<T>::init() const
{

}

template <class T>
vint Class<T>::getSource()
{
   return src;
}

//template <class T>
//RString Class<T>::getName()
//{
//   return typeid(T).name();
//}

template <class T>
RObject Class<T>::instantiate()
{
   return new T();
}

//template <class T>
//vbool Class<T>::isTypeOf(RObject obj)
//{
//   return dynamic_cast<T*>(obj.ref);
//}

template <class T>
RObject Class<T>::clone(RObject obj)
{
   Ref<T> tmp = new T();

   Ref<T> o_tmp = type_cast<T>(obj);

   (*tmp->operator->()) = (*o_tmp->operator->());

   return tmp;
}

} /* namespace aro */

#endif // !CORE_CLASS_IMP_H

