#include <aro/core/Array2D-impl.hpp>

namespace aro {

const Ref<Null>& Ref<Null>::get()
{
   return REF_NULL;
}

const Ref<Null> Ref<Null>::REF_NULL;

const Ref<Null>& nullref = Ref<Null>::get();


} /* namespace aro */
