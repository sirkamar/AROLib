#include <aro/util/Event.hpp>
#include <aro/core/impl/All.hpp>

namespace aro {

namespace util {

Event::Event(RObject src)
{
   setSource(src);
}

RObject Event::getSource()
{
   return source;
}

void Event::setSource(RObject src)
{
   if(src == nullref)
      ex_throw new ArgumentException("Illegal event source: null");
   
   source = src;
}

} /* namespace util */

} /* namespace aro */
