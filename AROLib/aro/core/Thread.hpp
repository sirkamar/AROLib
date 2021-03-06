#ifndef CORE_THREAD_H
#define CORE_THREAD_H

#include <aro/core/Runnable.hpp>
#include <aro/core/String.hpp>

namespace aro {

class Thread;

typedef Ref<Thread> RThread;
class Thread : public Object, public Runnable
{
   public:
      static const vint PRIORITY_LOWEST;
      static const vint PRIORITY_NORMAL;
      static const vint PRIORITY_HIGHEST;
      static const vint PRIORITY_ABOVE_NORMAL;
      static const vint PRIORITY_BELOW_NORMAL;
      
      static RThread currentThread();
      static void sleep(vlong millis);
      
      Thread();
      Thread(RString name);
      Thread(RRunnable aThread);
      Thread(RRunnable aThread, RString name);

      virtual void setPriority(vint priority) final;
      virtual void setName(RString name) final;
      virtual vbool isJoinable() final;
      virtual vint getPriority() final;
      virtual RString getName() final;
      virtual vbool isRunning() final;
      virtual void join() final;

      virtual RString toString();
      virtual void start();
      virtual void run();
   
   protected:
      virtual void finalize();
   
   private:
      RString name;
      const vint id;
      vbool running;
      std::thread st;
      RRunnable runPtr;
      
      vbool error = true;
      
      static vint threadCount;
	  
      static void threadMain(RThread);
   
   friend class MainThread;
   friend class ThreadLibrary;
};

} /* namespace aro */

#endif /* CORE_THREAD_H */
