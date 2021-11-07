#ifndef CORE_UTILS_OBJECTFACTORY_H
#define CORE_UTILS_OBJECTFACTORY_H

#include <aro/core/Interface.h>

namespace aro {

template <class T> class Class;

namespace io {

class ObjectInputStream;

class ObjectOutputStream;

}

class ObjectFactory final
{
   typedef RObject(*newfunc)(void);
   typedef RObject(*clonefunc)(RObject);
   
   template <class Function>
   struct Map
   {
      struct Node
      {
         int key;
         Node* next;
         Function value;
      };
      
      Map();
      ~Map();
      Function get(int key);
      void insert(int key, Function value);
      
      Node* listHead;
      std::mutex* mtx;
   };
   
   friend class Object;
   
   ObjectFactory() = default;
   
   template <class Function>
   static Map<Function>& getMap();

   template <class Function>
   static bool containsFunc(int type);

   friend class io::ObjectInputStream;
   
   friend class io::ObjectOutputStream;
   
   template <class T> friend class Class;

   static RObject createObject(int type);

   static RObject cloneObject(RObject obj);

   static void add(int type, newfunc func);
   
   static void add(int type, clonefunc func);
};

} /* namespace aro */

#endif /* CORE_UTILS_OBJECTFACTORY_H */
