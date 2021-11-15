#include <aro/core.hpp>
#include <aro/aws/Insets.hpp>

namespace aro {

namespace aws {

Insets::Insets()
{
   top = left = right = bottom = 0;
}

Insets::Insets(RInsets is)
{
   bottom = is->bottom;
   right = is->right;
   left = is->left;
   top = is->top;
}

Insets::Insets(vint top, vint left, vint bottom, vint right)
{
   set(top, left, bottom, right);
}

RString Insets::toString()
{
   return getType() + " [top:" + String::valueOf(top) +
          " left:" + String::valueOf(left) + " right:" +
          String::valueOf(right) + " bottom:" +
          String::valueOf(bottom) + "]";
}

vbool Insets::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Insets>(obj))
   {
      RInsets is = type_cast<Insets>(obj);
      
      return is->bottom==bottom && is->right==right &&
             is->left==left && is->top==top;
   }
   
   return false;
}

void Insets::readObject(io::RObjectInputStream is)
{
   top = is->readInt();
   left = is->readInt();
   right = is->readInt();
   bottom = is->readInt();
}

void Insets::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(top);
   os->writeInt(left);
   os->writeInt(right);
   os->writeInt(bottom);
}

void Insets::set(vint top, vint left, vint bottom, vint right)
{
   thisref->bottom = bottom;
   thisref->right = right;
   thisref->left = left;
   thisref->top = top;
}

} /* namespace aws */

} /* namespace aro */
