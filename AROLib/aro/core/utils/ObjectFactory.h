#ifndef CORE_UTILS_OBJECTFACTORY_H
#define CORE_UTILS_OBJECTFACTORY_H

#include <aro/core/Interface.h>

namespace aro {

namespace io {

class ObjectInputStream;

class ObjectOutputStream;

template <class T> class Class;

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
   
   friend class io::ObjectInputStream;
   
   friend class io::ObjectOutputStream;
   
   template <class T> friend class Class;

   static bool containsNewFunc(int type);

   static RObject createObject(int type);

   static bool containsCloneFunc(int type);

   static void add(int type, newfunc func);
   
   static void add(int type, clonefunc func);
   
   static RObject cloneObject(int type, RObject obj);
};

} /* namespace aro */

#endif /* CORE_UTILS_OBJECTFACTORY_H */
