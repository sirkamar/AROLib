#ifndef UTIL_TIMESTAMP_H
#define UTIL_TIMESTAMP_H

#include <aro/core.hpp>

namespace aro {

namespace util {

class Timestamp;
typedef Ref<Timestamp> RTimestamp;

class Timestamp : public Object, public io::Streamable<Timestamp>
{
   public:
      Timestamp();
      Timestamp(RTimestamp dt);
      Timestamp(vint day,vint month,vint year,vint hr,vint min,vint sec);
      
      void setTimestamp(vint day,vint month,vint year,vint hr,vint min,vint sec);
      
      void incrementSecond();
      void decrementSecond();
      void incrementDay();
      void decrementDay();
      
      vint getDay();
      vbool isLeap();
      vint getYear();
      vint getMonth();
      
      vint getHour();
      vint getMinute();
      vint getSecond();
      
      virtual RString toString();
      virtual vbool equals(RObject obj);
      
      virtual void readObject(io::RObjectInputStream is);
      virtual void writeObject(io::RObjectOutputStream os);
   
   protected:
      static const RArray<vint> daysInMonth;
      
      vint maxDays(vint month);
   
   private:
      vint hour, minute, second;
      vint day, month, year;
};

} /* namespace util */

} /* namespace aro */

#endif /* UTIL_TIMESTAMP_H */
