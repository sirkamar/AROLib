#ifndef CORE_UTILS_OBJECTFACTORY_IMPL_H
#define CORE_UTILS_OBJECTFACTORY_IMPL_H

#include <aro/core/utils/ObjectFactory.h>

namespace aro {

template <class Function>
ObjectFactory::Map<Function>::Map()
{
   listHead = nullptr;
   mtx = new std::mutex();
}

template <class Function>
ObjectFactory::Map<Function>::~Map()
{
   while(listHead != nullptr)
   {
      Node* tmp = listHead;
      listHead = tmp->next;
      delete tmp;
   }

   delete mtx;
}

template <class Function>
Function ObjectFactory::Map<Function>::get(int key)
{
   std::lock_guard<std::mutex> lock(*mtx);

   Node* head = listHead;

   while(head != nullptr)
   {
      if(head->key == key)
         return head->value;
      
      head = head->next;
   }

   return nullptr;
}

template <class Function>
void ObjectFactory::Map<Function>::insert(int key, Function value)
{
   std::lock_guard<std::mutex> lock(*mtx);

   Node* tmp = new Node();
   tmp->value = value;
   tmp->key = key;
   tmp->src.push_back(source);

   if(listHead == nullptr)
      listHead = tmp;
   else
   {
      tmp->next = listHead;
      listHead = tmp;
   }
}

template <class Function>
ObjectFactory::Map<Function>& ObjectFactory::getMap()
{
   static Map<Function> map;
   
   return map;
}

} /* namespace aro */

#endif /* CORE_UTILS_OBJECTFACTORY_IMPL_H */
