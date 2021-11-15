#include <exception>
#include <aro/core/System.hpp>
//#include <aro/core/Thread.hpp>
#include <aro/core/utils/Foreach.hpp>
#include <aro/core/StateException.hpp>
#include <aro/core/ThreadException.hpp>
#include <aro/core/utils/ThreadLibrary.hpp>

namespace aro {

vint Thread::threadCount = 0;

const vint Thread::PRIORITY_LOWEST           = -2;
const vint Thread::PRIORITY_BELOW_NORMAL     = -1;
const vint Thread::PRIORITY_NORMAL           = 0;
const vint Thread::PRIORITY_ABOVE_NORMAL     = 1;
const vint Thread::PRIORITY_HIGHEST          = 2;

Thread::Thread()
   :Thread(nullref, nullref)
{
   
}

Thread::Thread(RString str)
   :Thread(nullref, str)
{
   
}

Thread::Thread(RRunnable thread)
   :Thread(thread, nullref)
{
   
}

Thread::Thread(RRunnable thread, RString str)
   :id(threadCount++)
{
   if(str == nullref)
      str = "Thread-" + String::valueOf(id);
   
   this->name = str;
   runPtr = thread;
   running = false;
}

void Thread::setName(RString str)
{
   name = str;
}

void Thread::setPriority(vint priority)
{
   if(priority < PRIORITY_LOWEST || priority > PRIORITY_HIGHEST)
      ex_throw new ArgumentException("Invalid thread priority: " + String::valueOf(priority));
   
   SetThreadPriority(st.native_handle(), priority);
}

vint Thread::getPriority()
{
   int priority = GetThreadPriority(st.native_handle());
   
   if(priority < PRIORITY_LOWEST)
      return PRIORITY_LOWEST;
   
   if(priority > PRIORITY_HIGHEST)
      return PRIORITY_HIGHEST;
   
   return priority;
}

RThread Thread::currentThread()
{
   return ThreadLibrary::getThreadLibrary().get(std::this_thread::get_id());
}

void Thread::sleep(vlong millis)
{
   auto delay = std::chrono::milliseconds(millis);

   std::this_thread::sleep_for(delay);
}

void Thread::finalize()
{
   if(st.joinable())
      st.detach();
}

RString Thread::toString()
{
   std::stringstream ss;
   
   ss << this;
    
   return name + "@" + ss.str().c_str();
}

RString Thread::getName()
{
   return name;
}

vbool Thread::isJoinable()
{
   return st.joinable();
}

vbool Thread::isRunning()
{
   return running;
}

void Thread::start()
{
   if(running)
      ex_throw new StateException(name + " is already running");
   
   try {
      std::thread t(threadMain, thisref);
	  
      st.swap(t);
   }
   catch(std::exception e) {
      ex_throw new ThreadException(e.what());
   }
   catch(...) {
      ex_throw new ThreadException("Thread failed to start");
   }
}

void Thread::join()
{
   st.join();
}

void Thread::run()
{
   if(runPtr != nullref)
      runPtr->run();
}

void Thread::threadMain(RThread thread)
{
   ThreadLibrary::getThreadLibrary().insert(thread);
   
   thread->running = true;
   thread->error = true;
   
   try
   {
      thread->run();
	  
      thread->error = false;
   }
   catch(RException ex)
   {
      System::err->println("Unhandled Exception occurred in " + thread->name);
      
      ex->printException();
   }
   catch(Exception* exPtr)
   {
      RException ex = exPtr;
      
	   System::err->println("Unhandled Exception Pointer error in " +
                  thread->name + ". Use: ex_throw new " + ex->getType());
      
      ex->printException();
   }
   catch(std::exception e)
   {
      System::err->println("Unhandled std::exception occurred in " +
                  thread->name + ": " + e.what());
   }
   catch(...)
   {
      System::err->println("Unknown error occurred in " + thread->name);
   }

   thread->running = false;
   
   ThreadLibrary::getThreadLibrary().remove(thread);
}

} /* namespace aro */
