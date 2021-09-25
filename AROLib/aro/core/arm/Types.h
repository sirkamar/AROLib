#ifndef ARM_TYPES_H
#define ARM_TYPES_H

namespace aro{

typedef int vint;        // integer 32-bits
typedef bool vbool;      // boolean 1-bit
typedef short vshort;    // short integer 16-bits
typedef float vfloat;    // floating point 32-bits
typedef wchar_t vchar;   // character 16-bits (windows)
typedef double vdouble;  // double floating point 64-bits
typedef long long vlong; // long integer 64-bits

/*
class vint;
class vbool;
class vchar;
class vlong;
class vshort;
class vfloat;
class vdouble;

class vshort
{
   public:
      vshort(short val);
      vshort() = default;
      vshort(vshort&&) = default;
      vshort(const vshort&) = default;

      vshort& operator=(short val);
      vshort& operator=(vshort&& val) = default;
      vshort& operator=(const vshort& val) = default;

      vint operator+(const vint& val);
      vshort operator+(const vshort& val);
      vlong operator+(const vlong& val);
      vfloat operator+(const vfloat& val);
      vdouble operator+(const vdouble& val);

      vint operator-(const vint& val);
      vshort operator-(const vshort& val);
      vlong operator-(const vlong& val);
      vfloat operator-(const vfloat& val);
      vdouble operator-(const vdouble& val);

      vint operator*(const vint& val);
      vshort operator*(const vshort& val);
      vlong operator*(const vlong& val);
      vfloat operator*(const vfloat& val);
      vdouble operator*(const vdouble& val);

      vint operator/(const vint& val);
      vshort operator/(const vshort& val);
      vlong operator/(const vlong& val);
      vfloat operator/(const vfloat& val);
      vdouble operator/(const vdouble& val);

      vint operator%(const vint& val);
      vshort operator%(const vshort& val);
      vlong operator%(const vlong& val);
      vfloat operator%(const vfloat& val);
      vdouble operator%(const vdouble& val);

   private:
      short value;

      vshort(char);
      vshort(wchar_t);
};

class vint
{
   public:
      vint(int val);
      vint() = default;
      vint(const vchar& val);
      vint(const vshort& val);
      vint(vint&& val) = default;
      vint(const vint& val) = default;
      
      vint& operator=(int val);
      vint& operator=(const vchar& val);
      vint& operator=(const vshort& val);
      vint& operator=(vint&& val) = default;
      vint& operator=(const vint& val) = default;
      
      vint operator+(const vint& val);
      vint operator+(const vchar& val);
      vint operator+(const vshort& val);
      vlong operator+(const vlong& val);
      vfloat operator+(const vfloat& val);
      vdouble operator+(const vdouble& val);
      
      vint operator-(const vint& val);
      vint operator-(const vchar& val);
      vint operator-(const vshort& val);
      vlong operator-(const vlong& val);
      vfloat operator-(const vfloat& val);
      vdouble operator-(const vdouble& val);
      
      vint operator*(const vint& val);
      vint operator*(const vshort& val);
      vlong operator*(const vlong& val);
      vfloat operator*(const vfloat& val);
      vdouble operator*(const vdouble& val);
      
      vint operator/(const vint& val);
      vint operator/(const vshort& val);
      vlong operator/(const vlong& val);
      vfloat operator/(const vfloat& val);
      vdouble operator/(const vdouble& val);
      
      vint operator%(const vint& val);
      vint operator%(const vshort& val);
      vlong operator%(const vlong& val);
      vfloat operator%(const vfloat& val);
      vdouble operator%(const vdouble& val);

      vbool operator>(const vint& val);
      vbool operator>(const vchar& val);
      vbool operator>(const vshort& val);
      vbool operator>(const vlong& val);
      vbool operator>(const vfloat& val);
      vbool operator>(const vdouble& val);

      vbool operator<(const vint& val);
      vbool operator<(const vchar& val);
      vbool operator<(const vshort& val);
      vbool operator<(const vlong& val);
      vbool operator<(const vfloat& val);
      vbool operator<(const vdouble& val);

      vbool operator>=(const vint& val);
      vbool operator>=(const vchar& val);
      vbool operator>=(const vshort& val);
      vbool operator>=(const vlong& val);
      vbool operator>=(const vfloat& val);
      vbool operator>=(const vdouble& val);

      vbool operator<=(const vint& val);
      vbool operator<=(const vchar& val);
      vbool operator<=(const vshort& val);
      vbool operator<=(const vlong& val);
      vbool operator<=(const vfloat& val);
      vbool operator<=(const vdouble& val);

      vbool operator==(const vint& val);
      vbool operator==(const vchar& val);
      vbool operator==(const vshort& val);
      vbool operator==(const vlong& val);
      vbool operator==(const vfloat& val);
      vbool operator==(const vdouble& val);

      vbool operator!=(const vint& val);
      vbool operator!=(const vchar& val);
      vbool operator!=(const vshort& val);
      vbool operator!=(const vlong& val);
      vbool operator!=(const vfloat& val);
      vbool operator!=(const vdouble& val);

      vint& operator++();
      vint& operator--();
      vint operator++(int);
      vint operator--(int);
      operator int() const;


   private:
      int value;

      vint(char);
      vint(wchar_t);
};

class vlong
{
   public:
      vlong() = default;
      vlong(long long val);
      vlong(const vint& val);
      vlong(const vshort& val);
      vlong(vlong&& val) = default;
      vlong(const vlong& val) = default;

      vlong& operator=(long long val);
      vlong& operator=(const vint& val);
      vlong& operator=(const vshort& val);
      vlong& operator=(vlong&& val) = default;
      vlong& operator=(const vlong& val) = default;

      vlong operator+(const vint& val);
      vlong operator+(const vshort& val);
      vlong operator+(const vlong& val);
      vfloat operator+(const vfloat& val);
      vdouble operator+(const vdouble& val);

      vlong operator-(const vint& val);
      vlong operator-(const vshort& val);
      vlong operator-(const vlong& val);
      vfloat operator-(const vfloat& val);
      vdouble operator-(const vdouble& val);

      vlong operator*(const vint& val);
      vlong operator*(const vshort& val);
      vlong operator*(const vlong& val);
      vfloat operator*(const vfloat& val);
      vdouble operator*(const vdouble& val);

      vlong operator/(const vint& val);
      vlong operator/(const vshort& val);
      vlong operator/(const vlong& val);
      vfloat operator/(const vfloat& val);
      vdouble operator/(const vdouble& val);

      vlong operator%(const vint& val);
      vlong operator%(const vshort& val);
      vlong operator%(const vlong& val);
      vfloat operator%(const vfloat& val);
      vdouble operator%(const vdouble& val);

   private:
      long long value;

      vlong(char);
      vlong(wchar_t);
};

class vfloat
{
   public:
      vfloat(float val);
      vfloat() = default;
      vfloat(const vint& val);
      vfloat(const vlong& val);
      vfloat(const vshort& val);
      vfloat(vfloat&&) = default;
      vfloat(const vfloat&) = default;

      vfloat& operator=(const vint& val);
      vfloat& operator=(const vlong& val);
      vfloat& operator=(const vshort& val);
      vfloat& operator=(vfloat&& val) = default;
      vfloat& operator=(const vfloat& val) = default;

      vfloat operator+(const vint& val);
      vfloat operator+(const vshort& val);
      vlong operator+(const vlong& val);
      vfloat operator+(const vfloat& val);
      vdouble operator+(const vdouble& val);

      vfloat operator-(const vint& val);
      vfloat operator-(const vshort& val);
      vlong operator-(const vlong& val);
      vfloat operator-(const vfloat& val);
      vdouble operator-(const vdouble& val);

      vfloat operator*(const vint& val);
      vfloat operator*(const vshort& val);
      vlong operator*(const vlong& val);
      vfloat operator*(const vfloat& val);
      vdouble operator*(const vdouble& val);

      vfloat operator/(const vint& val);
      vfloat operator/(const vshort& val);
      vlong operator/(const vlong& val);
      vfloat operator/(const vfloat& val);
      vdouble operator/(const vdouble& val);

      vfloat operator%(const vint& val);
      vfloat operator%(const vshort& val);
      vlong operator%(const vlong& val);
      vfloat operator%(const vfloat& val);
      vdouble operator%(const vdouble& val);

   private:
      float value;

      vfloat(char);
      vfloat(wchar_t);
};

class vdouble
{
   public:
      vdouble(double val);
      vdouble() = default;
      vdouble(const vint&);
      vdouble(const vlong&);
      vdouble(const vshort&);
      vdouble(const vfloat&);
      vdouble(vdouble&&) = default;
      vdouble(const vdouble&) = default;

      vdouble& operator=(double val);
      vdouble& operator=(const vint& val);
      vdouble& operator=(const vlong& val);
      vdouble& operator=(const vshort& val);
      vdouble& operator=(const vfloat& val);
      vdouble& operator=(vdouble&& val) = default;
      vdouble& operator=(const vdouble& val) = default;

      vdouble operator+(const vint& val);
      vdouble operator+(const vshort& val);
      vlong operator+(const vlong& val);
      vfloat operator+(const vfloat& val);
      vdouble operator+(const vdouble& val);

      vdouble operator-(const vint& val);
      vdouble operator-(const vshort& val);
      vlong operator-(const vlong& val);
      vfloat operator-(const vfloat& val);
      vdouble operator-(const vdouble& val);

      vdouble operator*(const vint& val);
      vdouble operator*(const vshort& val);
      vlong operator*(const vlong& val);
      vfloat operator*(const vfloat& val);
      vdouble operator*(const vdouble& val);

      vdouble operator/(const vint& val);
      vdouble operator/(const vshort& val);
      vlong operator/(const vlong& val);
      vfloat operator/(const vfloat& val);
      vdouble operator/(const vdouble& val);

      vdouble operator%(const vint& val);
      vdouble operator%(const vshort& val);
      vlong operator%(const vlong& val);
      vfloat operator%(const vfloat& val);
      vdouble operator%(const vdouble& val);

   private:
      double value;

      vdouble(char);
      vdouble(wchar_t);
};

class vbool
{
   public:
      static const vbool VTRUE;
      static const vbool VFALSE;

      vbool() = default;
      vbool(vbool&&) = default;
      vbool(const vbool&) = default;

      vbool& operator=(bool val);
      vbool& operator=(vbool&& val) = default;
      vbool& operator=(const vbool& val) = default;

      operator bool() const;
      bool operator!() const;

   private:
      bool value;

      vbool(const bool& val);
      vbool& operator=(const void*);
      //template <class T> vbool(T val);
};

extern const vbool& vtrue;
extern const vbool& vfalse;

class vchar
{
   public:
      vchar(char val);
      vchar() = default;
      vchar(vchar&&) = default;
      vchar(const vchar&) = default;

      vchar& operator=(char val);
      vchar& operator=(vchar&& val) = default;
      vchar& operator=(const vchar& val) = default;

      vchar operator+(const vint& val);
      vchar operator+(const vshort& val);
      vchar operator+(const vchar& val);

   private:
      char value;

      vchar(int);
      vchar(short);
};
*/
} /* namespace aro */

#endif /* ARM_TYPES_H */
