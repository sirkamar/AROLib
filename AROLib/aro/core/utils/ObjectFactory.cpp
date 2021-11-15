#include <aro/core/utils/Foreach.hpp>

namespace aro {

RObject ObjectFactory::createObject(int type)
{
   if(newfunc func = getMap<newfunc>().get(type))
      return func();
   
   return nullref;
}

RObject ObjectFactory::cloneObject(RObject obj)
{
    vint typeId = obj->getType()->hashCode();

    if (clonefunc func = getMap<clonefunc>().get(typeId))
        return func(obj);

    return nullref;
}

void ObjectFactory::add(int type, newfunc func)
{
   if(!containsFunc<newfunc>(type))
      getMap<newfunc>().insert(type, func);
}

void ObjectFactory::add(int type, clonefunc func)
{
   if(!containsFunc<clonefunc>(type))
      getMap<clonefunc>().insert(type, func);
}

} /* namespace aro */
