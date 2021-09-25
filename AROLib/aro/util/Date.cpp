#include <aro/util/Date.h>

namespace aro {

namespace util {

const RArray<String> Date::daysOfWeek = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

const RArray<String> Date::months =  {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

const RArray<vint> Date::daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date()
{
   SYSTEMTIME time;
   
   GetLocalTime(&time);
   
   setDate(time.wDay, time.wMonth, time.wYear);
}

Date::Date(RDate aDate)
{
   setDate(aDate->day, aDate->month, aDate->year);
}

Date::Date(vint dd, vint mm, vint yyyy)
{
   setDate(dd, mm, yyyy);
}

vint Date::getDay()
{
   return day;
}

vint Date::getMonth()
{
   return month;
}

vint Date::getYear()
{
   return year;
}

vbool Date::isLeap()
{
   return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

void Date::decrement()
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

void Date::increment()
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

RString Date::getLongDate()
{
   return getShortDate();
}

RString Date::getShortDate()
{
   return (day<10 ? "0" : "") + String::valueOf(day) +
   "-" + months[month-1] + "-" + String::valueOf(year);
}

RString Date::toString()
{
   return getShortDate();
}

vbool Date::equals(RObject obj)
{
   if(obj == thisref)
      return true;
   
   if(type_of<Date>(obj))
   {
      RDate dt = type_cast<Date>(obj);
      
      return (dt->day == day && dt->month == month && dt->year == year);
   }
   
   return false;
}

RDate Date::valueOf(RString str)
{
   if(str == nullref)
      ex_throw new ArgumentException("Invalid date: null");
   
   vint dd, mm, yyyy;
   vint firstDash, secondDash;
   
   firstDash = str->indexOf('-');
   secondDash = str->indexOf('-', firstDash+1);
   
   if((firstDash > 0) && (secondDash > 0) && (secondDash < str->length()-1))
   {
	   dd = Int::parse(str->substring(0, firstDash));	 
	   mm = Int::parse(str->substring(firstDash+1, secondDash));
      yyyy = Int::parse(str->substring(secondDash+1));
	}
	else
      ex_throw new ArgumentException("Date format dd-mm-yyyy required");
   
   return new Date(dd, mm, yyyy);
}

void Date::setDate(vint dd, vint mm, vint yyyy)
{
   if(yyyy<1970)
      ex_throw new ArgumentException("Date cannot be earlier than 01-01-1970");
   
   if(mm<1 || mm>12 || dd<1 || dd>maxDays(mm))
      ex_throw new ArgumentException("Invalid Date: " + String::valueOf(dd) +
                "-" + String::valueOf(mm) + "-" + String::valueOf(yyyy));
   
   year = yyyy; month = mm; day = dd;
}

vint Date::maxDays(vint mm)
{
   if(mm == 2 && isLeap())
      return 29;
   
   return daysInMonth[mm-1];
}

} /* namespace util */

} /* namespace aro */
