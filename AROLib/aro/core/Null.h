#ifndef CORE_NULL_H
#define CORE_NULL_H

#include <aro/core/Object.h>

namespace aro {

class Null final : public Object
{
   Null() = default;
   
   friend class Ref<Null>;
};

} /* namespace aro */

#endif /* CORE_NULL_H */
