#ifndef ARO_ARM_REFNULL_H
#define ARO_ARM_REFNULL_H

#include <aro/core/arm/Cfg.hpp>
#include <aro/core/arm/Types.hpp>

namespace aro {

class Null;
template <class T> class Ref;

template <>
class Ref<Null>
{
   public:
      static const Ref<Null> REF_NULL;
   
   private:
      Ref() = default;
      Ref(const Ref<Null>&) = delete;
      Ref<Null>& operator=(const Ref<Null>&) = delete;
};

extern const Ref<Null>& nullref;

} /* namespace aro */

#endif /* ARO_ARM_REFNULL_H */
