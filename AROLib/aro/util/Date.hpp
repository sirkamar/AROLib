#include <aro/core.hpp>

namespace aro {

namespace util {

class Date;                             // forward declaration
typedef Ref<Date> RDate;                // reference declaration

class Date : public Object
{
   public:
      Date();
      Date(RDate aDate);
      Date(vint day, vint month, vint year);
      
      vint getDay();
      vint getMonth();
      vint getYear();
      vbool isLeap();
      
      void decrement();
      void increment();
      
      RString getLongDate();
      RString getShortDate();
      
      virtual RString toString();      
      virtual vbool equals(RObject obj);
      
      static RDate valueOf(RString str);
      
      void setDate(vint day, vint month, vint year);
   
   protected:
      static const RArray<String> daysOfWeek;
      static const RArray<vint> daysInMonth;
      static const RArray<String> months;
      
      vint maxDays(vint month);
   
   private:
      vint day, month, year;
};

} /* namespace util */

} /* namespace aro */
