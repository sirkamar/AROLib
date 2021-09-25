#include <cmath>
#include <ctime>
#include <cstdlib>
#include <aro/core/utils/Foreach.h>

namespace aro {

vbool Math::isSeeded = false;

const vdouble Math::E = 2.7182818284590452354;
const vdouble Math::PI = 3.14159265358979323846;

Math::Math() { }

vint Math::abs(vint x)
{
   return (x<0) ? -x : x;
}

vdouble Math::random()
{
   if(!isSeeded)
   {
      srand((vint)time(nullptr));
      isSeeded = true;
   }
   
   return (rand() % 10) / 10.0;
}

vlong Math::abs(vlong x)
{
   return (x<0) ? -x : x;
}

vfloat Math::abs(vfloat x)
{
   return (x<0) ? -x : x;
}

vint Math::round(vfloat x)
{
   return (vint)floor(x + 0.5);
}

vfloat Math::ceil(vfloat x)
{
   return ::ceil(x);
}

vfloat Math::floor(vfloat x)
{
   return ::floor(x);
}

vdouble Math::abs(vdouble x)
{
   return (x<0) ? -x : x;
}

vdouble Math::sin(vdouble x)
{
   return ::sin(x);
}

vdouble Math::cos(vdouble x)
{
   return ::cos(x);
}

vdouble Math::tan(vdouble x)
{
   return ::tan(x);
}

vdouble Math::log(vdouble x)
{
   return ::log(x);
}

vdouble Math::exp(vdouble x)
{
   return ::exp(x);
}

vlong Math::round(vdouble x)
{
   return (vlong)floor(x + 0.5);
}

vint Math::factorial(vint x)
{
   if(x <= 1)
      return 1;
   
   return x * factorial(x-1);
}

vdouble Math::sqrt(vdouble x)
{
   return ::sqrt(x);
}

vdouble Math::ceil(vdouble x)
{
   return ::ceil(x);
}

vdouble Math::floor(vdouble x)
{
   return ::floor(x);
}

vdouble Math::log10(vdouble x)
{
   return ::log10(x);
}

vint Math::maximum(vint x, vint y)
{
   return (x>=y) ? x : y;
}

vint Math::minimum(vint x, vint y)
{
   return (x<=y) ? x : y;
}

vlong Math::maximum(vlong x, vlong y)
{
   return x > y ? x : y;
}

vlong Math::minimum(vlong x, vlong y)
{
   return x < y ? x : y;
}

vdouble Math::toDegrees(vdouble rad)
{
   return (vdouble) (rad * 180.0 / PI);
}

vdouble Math::toRadians(vdouble deg)
{
   return (vdouble) (deg / 180.0 * PI);
}

vdouble Math::pow(vdouble x, vdouble y)
{
   return ::pow(x, y);
}

vfloat Math::maximum(vfloat x, vfloat y)
{
   return x > y ? x : y;
}

vfloat Math::minimum(vfloat x, vfloat y)
{
   return x < y ? x : y;
}

vdouble Math::maximum(vdouble x, vdouble y)
{
   return x > y ? x : y;
}

vdouble Math::minimum(vdouble x, vdouble y)
{
   return x < y ? x : y;
}

} /* namespace aro */
