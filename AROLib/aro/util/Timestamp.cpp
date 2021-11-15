#include <aro/util/Timestamp.hpp>

namespace aro {

namespace util {

const RArray<vint> Timestamp::daysInMonth = {31,28,31,30,31,30,31,31,30,31,30,31};

Timestamp::Timestamp()
{
   SYSTEMTIME st;
   
   GetLocalTime(&st);
   
   setTimestamp(st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);
}

Timestamp::Timestamp(RTimestamp ts)
{
   setTimestamp(ts->day,ts->month,ts->year,ts->hour,ts->minute,ts->second);
}

Timestamp::Timestamp(vint dd, vint mm, vint yyyy, vint hr, vint min, vint sec)
{
   setTimestamp(dd, mm, yyyy, hr, min, sec);
}

vbool Timestamp::isLeap()
{
   return (year%400==0 ||
    (year%4==0 && year%100!=0));
}

vint Timestamp::getYear()
{
   return year;
}

vint Timestamp::getMonth()
{
   return month;
}

vint Timestamp::getDay()
{
   return day;
}

vint Timestamp::getHour()
{
   return hour;
}

vint Timestamp::getMinute()
{
   return minute;
}

vint Timestamp::getSecond()
{
   return second;
}

void Timestamp::incrementDay()
{
   day++;
   
   if(day > maxDays(month))
   {
      month++;
      day = 1;
      
      if(month > 12)
      {
         year++;
         month = 1;
      }
   }
}

void Timestamp::decrementDay()
{
   if(day == 1 && month == 1 && year == 1970)
      return; // cannot go beyond base date
   
   day--;
   
   if(day < 1)
   {
      month--;
      
      if(month < 1)
      {
         year--;
         month = 12;
      }
      
      day = maxDays(month);
   }
}

void Timestamp::incrementSecond()
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
         {
            hour = 0;
            incrementDay();
         }
      }
   }
}

void Timestamp::decrementSecond()
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
         {
            hour = 23;
            decrementDay();
         }
      }
   }
}

RString Timestamp::toString()
{
   return String::valueOf(year) + "-" +
         (month<10 ? "0" : "") + String::valueOf(month) + "-" +
         (day<10 ? "0" : "") + String::valueOf(day) + " " +
         (hour<10 ? "0" : "") + String::valueOf(hour) + ":" +
         (minute<10 ? "0" : "") + String::valueOf(minute) + ":" +
         (second<10 ? "0" : "") + String::valueOf(second);
}

vbool Timestamp::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Timestamp>(obj))
   {
      RTimestamp ts = type_cast<Timestamp>(obj);
      
      return (ts->year == year && ts->month == month && ts->day == day &&
            ts->hour == hour && ts->minute == minute && ts->second == second);
   }
   
   return false;
}

void Timestamp::setTimestamp(vint yyyy, vint mm, vint dd, vint hr, vint min, vint sec)
{
   if(yyyy<1970)
      ex_throw new ArgumentException("Date cannot be earlier than 1970-01-01");
   
   if(mm<1 || mm>12 || dd<1 || dd>maxDays(mm))
      ex_throw new ArgumentException("Invalid Date: " + String::valueOf(dd) +
                "-" + String::valueOf(mm) + "-" + String::valueOf(yyyy));
   
   if((hr|min|sec)<0 || hr>23 || min>59 || sec>59)
      ex_throw new ArgumentException("Invalid time: " + String::valueOf(hr)+
                ":" + String::valueOf(min) + ":" + String::valueOf(sec));
   
   hour = hr; minute = min; second = sec;
   
   year = yyyy; month = mm; day = dd;
}

vint Timestamp::maxDays(vint mm)
{
   if(isLeap() && mm == 2)
      return 29;
   
   return daysInMonth[mm-1];
}

void Timestamp::writeObject(io::RObjectOutputStream os)
{
   os->writeInt(day);
   os->writeInt(month);
   os->writeInt(year);
   
   os->writeInt(hour);
   os->writeInt(minute);
   os->writeInt(second);
}

void Timestamp::readObject(io::RObjectInputStream is)
{
   day = is->readInt();
   month = is->readInt();
   year = is->readInt();
   
   hour = is->readInt();
   minute = is->readInt();
   second = is->readInt();
}

} /* namespace util */

} /* namespace aro */
