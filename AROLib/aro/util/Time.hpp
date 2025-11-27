#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <aro/core.hpp>

namespace aro {

namespace util {

class Time;
typedef Ref<Time> RTime;

class Time extends public Object
{
   public:
      Time(void);
      Time(RTime aTime);
      Time(vint hour, vint minute, vint second);
      
      vint getHour();
      vint getMinute();
      vint getSecond();
      
      void decrement();
      void increment();
      
      RString getUTCTime();
      RString getStandardTime();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      
      static RTime valueOf(RString str);
      
      void setTime(vint hour, vint minute, vint second);
   
   private:
      vint hour, minute, second;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_TIME_H */
