#ifndef AWS_SYSTEMMONITOR_H
#define AWS_SYSTEMMONITOR_H

#include <aro/core/Thread.hpp>

namespace aro {

namespace aws {

class SystemMonitor;
typedef Ref<SystemMonitor> RSystemMonitor;

class SystemMonitor final : public Thread
{
   class Key;
   
   typedef Ref<Key> RKey;
   
   public:
      vbool isRunning();
      virtual void run();
   
   protected:
      virtual void finalize();
   
   private:
      void stop();
      SystemMonitor();
      
      vbool monitorRunning;
      
      static const RArray<Key> KEYS;
      
      //static const RSystemMonitor kde;
      
      class Key : public Object
      {
         public:
            vint code;
            vbool isDown;
            vchar standard;
            vchar withShift;
            vchar withControl;
            vchar withControlShift;
            
            Key(vint code =0);
            Key(vint code, vchar standard);
            Key(vint code, vchar standard, vchar shift);
            Key(vint code, vchar standard, vchar shift, vchar cntrl);
            Key(vint code, vchar standard, vchar shift, vchar cntrl, vchar cntrlShift);
      };
   
   friend class Window;
};

} /* namespace aws */

} /* namespace aro */

#endif /* AWS_SYSTEMMONITOR_H */
