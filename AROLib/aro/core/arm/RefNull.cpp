#include <aro/core/utils/Foreach.hpp>

namespace aro {

const Ref<Null>& Ref<Null>::get()
{
   return REF_NULL;
}

const Ref<Null> Ref<Null>::REF_NULL;

const Ref<Null>& nullref = Ref<Null>::get();


} /* namespace aro */
