#ifndef AWS_DIMENSION_H
#define AWS_DIMENSION_H

#include <aro/core.hpp>

namespace aro {

namespace aws {

class Dimension;
typedef Ref<Dimension> RDimension;

class Dimension : public Object, public io::Streamable<Dimension>
{
   public:
      vint width;
      vint height;
      
	   Dimension();
      Dimension(RDimension size);
      Dimension(vint width,vint height);
      
      virtual vint getWidth();
      virtual vint getHeight();
      virtual RString toString();
      virtual void setWidth(vint width);
      virtual void setHeight(vint height);
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
      virtual void setSize(vint width,vint height);
      virtual void setSize(RDimension size);
      virtual vbool equals(RObject obj);
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_DIMENSION_H */
