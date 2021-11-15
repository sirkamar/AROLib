#include <aro/util/Time.hpp>

namespace aro {

namespace util {

Time::Time()
{
   SYSTEMTIME time;
   
   GetLocalTime(&time);
   
   setTime(time.wHour,time.wMinute,time.wSecond);
}

Time::Time(RTime aTime)
{
   setTime(aTime->hour, aTime->minute, aTime->second);
}

Time::Time(vint hr, vint min, vint sec)
{
   setTime(hr, min, sec);
}

vint Time::getHour()
{
   return hour;
}

vint Time::getMinute()
{
   return minute;
}

vint Time::getSecond()
{
   return second;
}

void Time::decrement()
{
   second--;
   
   if(second < 0)
   {
      minute--;
      second = 59;
      
      if(minute < 0)
      {
         hour--;
         minute = 59;
         
         if(hour < 0)
            hour = 23;
      }
   }
}

void Time::increment()
{
   second++;
   
   if(second > 59)
   {
      minute++;
      second = 0;
      
      if(minute > 59)
      {
         hour++;
         minute = 0;
         
         if(hour > 23)
            hour = 0;
      }
   }
}

RString Time::getUTCTime()
{
   return (hour<10 ? "0" : "") + String::valueOf(hour) +
    ":" + (minute<10 ? "0" : "") + String::valueOf(minute) +
      ":" + (second<10 ? "0" : "") + String::valueOf(second);
}

RString Time::getStandardTime()
{
   return String::valueOf(hour==0 || hour==12 ? 12 : hour%12) +
   ":" + (minute<10 ? "0" : "") + String::valueOf(minute) +
   ":" + (second<10 ? "0" : "") + String::valueOf(second) +
   " " + (hour<12 ? "AM" : "PM");
}

RString Time::toString()
{
   return getUTCTime();
}

vbool Time::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Time>(obj))
   {
      RTime tm = type_cast<Time>(obj);
      
      return (tm->hour == hour && tm->minute == minute && tm->second == second);
   }
   
   return false;
}

RTime Time::valueOf(RString str)
{
   if(str == nullref)
      ex_throw new ArgumentException("Invalid time: null");
   
   vint hr, min, sec;
   vint firstColon, secondColon;
   
   firstColon = str->indexOf(':');
   secondColon = str->indexOf(':', firstColon+1);
   
   if((firstColon > 0) && (secondColon > 0) && (secondColon < str->length()-1))
   {
      hr = Int::parse(str->substring(0, firstColon));
      min = Int::parse(str->substring(firstColon+1, secondColon));
      sec = Int::parse(str->substring(secondColon+1));
   }
   else
      ex_throw new ArgumentException("Time format hh:mm::ss required");
   
   return new Time(hr, min, sec);
}

void Time::setTime(vint hr, vint min, vint sec)
{
   if((hr|min|sec)<0 || hr>23 || min>59 || sec>59)
      ex_throw new ArgumentException("Invalid time: " + String::valueOf(hr)+
                ":" + String::valueOf(min) + ":" + String::valueOf(sec));
   
   hour = hr; minute = min; second = sec;
}

} /* namespace util */

} /* namespace aro */
