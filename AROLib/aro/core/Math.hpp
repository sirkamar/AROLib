#ifndef CORE_MATH_H
#define CORE_MATH_H

#include <aro/core/Object.hpp>

namespace aro {

/** The abstract Math class, dispite being a bonified
 * subclass of Object, provides only public static
 * member functions and CANNOT be inherited */
class Math final extends public Object
{
   public:
      static const vdouble E; // The value of e (the base of natural logarithms)
      static const vdouble PI; // The vlue of pi (ratio of circumference to diameter)
      
      static vint abs(vint x); // Returns the absoute value of a number |x|
      static vdouble random(); // Returns a random vdouble in the range 0.0 to 0.9
      static vlong abs(vlong x); // Returns the absoute value of a number |x|
      static vfloat abs(vfloat x); // Returns the absoute value of a number |x|
      static vfloat ceil(vfloat x); // Returns the next highest whole number
      static vfloat floor(vfloat x); // Returns the next lowest whole number
      static vdouble abs(vdouble x); // Returns the absoute value of a number |x|
      static vdouble sin(vdouble x); // Returns the trigonometric sine of a number
      static vdouble cos(vdouble x); // Returns the trigonometric consine of a number
      static vdouble tan(vdouble x); // Returns the trigonometric tangent of a number
      static vdouble log(vdouble x); // Returns the natural log of a number
      static vdouble exp(vdouble x); // Returns the value of e to a number
      static vint factorial(vint x); // Returns the factorial of a given integer
      static vdouble sqrt(vdouble x); // Returns the square root of a number
      static vdouble ceil(vdouble x); // Returns the next highest whole number
      static vdouble floor(vdouble x); // Returns the next lowest whole number
      static vdouble log10(vdouble x); // Returns the log base 10 of a number
      static vdouble round(vdouble x); // Rounds a number to a whole number
      static vint maximum(vint x,vint y); // Returns the largest of two integers
      static vint minimum(vint x,vint y); // Returns the smallest of two integers
      static vlong maximum(vlong x,vlong y); // Returns the largest of two integers
      static vlong minimum(vlong x,vlong y); // Returns the smallest of two integers
      static vdouble toDegrees(vdouble rad); // Converts a radian value to degrees
      static vdouble toRadians(vdouble deg); // Converts a value in degrees to radians
      static vdouble pow(vdouble x,vdouble y); // Returns the value of x to the power of y
      static vfloat maximum(vfloat x,vfloat y); // Returns the lagest of two doubles
      static vfloat minimum(vfloat x,vfloat y); // Returns the smallest of two doubles
      static vdouble maximum(vdouble x,vdouble y); // Returns the lagest of two doubles
      static vdouble minimum(vdouble x,vdouble y); // Returns the smallest of two doubles
      static vdouble round(vdouble x, vint precision); // Rounds a number to the specified decimal precision

   private:
      static vbool isSeeded; // if srand has been seed
      
      Math() = default; // Prevents Instantiation
};

} /* namespace aro */

#endif /* CORE_MATH_H */
