#include <aro/core/utils/Foreach.h>

namespace aro {

//ObjectFactory::Map::Map()
//{
//   listHead = nullptr;
//   mtx = new std::mutex();
//}
//
//ObjectFactory::Map::~Map()
//{
//   while(listHead != nullptr)
//   {
//      Node* tmp = listHead;
//      listHead = tmp->next;
//      delete tmp;
//   }
//
//   delete mtx;
//}
//
//ObjectFactory::newfunc ObjectFactory::Map::get(int source, int key)
//{
//   std::lock_guard<std::mutex> lock(*mtx);
//   
//   Node* head = listHead;
//   
//   while(head != nullptr)
//   {
//      if(head->key == key)
//      {
//         for(int n : head->src)
//            if(n == source)
//               return head->value;
//      }
//      
//      head = head->next;
//   }
//   
//   return nullptr;
//}
//
//void ObjectFactory::Map::insert(int source, int key, newfunc value)
//{
//   std::lock_guard<std::mutex> lock(*mtx);
//   
//   Node* tmp = new Node();
//   tmp->value = value;
//   tmp->key = key;
//   tmp->src.push_back(source);
//   
//   if(listHead == nullptr)
//      listHead = tmp;
//   else
//   {
//      tmp->next = listHead;
//      listHead = tmp;
//   }
//}
//
//ObjectFactory::Map& ObjectFactory::getMap()
//{
//   static Map map;
//   
//   return map;
//}

bool ObjectFactory::containsNewFunc(int type)
{
   if(getMap<newfunc>().get(type))
      return true;
   
   return false;
}

bool ObjectFactory::containsCloneFunc(int type)
{
   if(getMap<clonefunc>().get(type))
      return true;

   return false;
}

RObject ObjectFactory::createObject(int type)
{
   if(newfunc func = getMap<newfunc>().get(type))
      return func();
   
   return nullref;
}

void ObjectFactory::add(int type, newfunc func)
{
   if(!containsNewFunc(type))
      getMap<newfunc>().insert(type, func);
}

void ObjectFactory::add(int type, clonefunc func)
{
   if(!containsCloneFunc(type))
      getMap<clonefunc>().insert(type, func);
}

RObject ObjectFactory::cloneObject(int type, RObject obj)
{
   if(clonefunc func = getMap<clonefunc>().get(type))
      return func(obj);

   return nullref;
}

} /* namespace aro */
