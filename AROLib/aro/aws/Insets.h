#ifndef AWS_INSETS_H
#define AWS_INSETS_H

#include <aro/core.h>

namespace aro {

namespace aws {

class Insets;
typedef Ref<Insets> RInsets;

class Insets : public Object, public io::Streamable<Insets>
{
   public:
      vint top, left;
      vint right, bottom;
      
      Insets();
      Insets(RInsets ins);
      Insets(vint top, vint left, vint bottom, vint right);
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
      virtual void set(vint top, vint left, vint bottom, vint right);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_INSETS_H */
