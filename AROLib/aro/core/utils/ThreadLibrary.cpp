#include <aro/core/utils/ThreadLibrary.hpp>

namespace aro {

ThreadLibrary::ThreadLibrary()
{
   mutex = new Object();
   
   threadList = new util::Vector<Thread>();
}

void ThreadLibrary::joinAllThreads()
{
	do
	{
      RThread subject;
      
      sync_lock(mutex)
      {
         while(!listChanged)
            mutex->wait();
         
         listChanged = false;
         
         //search for a joinable thread in vector
		   for(auto thread : threadList->iterator())
		   {
			   if(thread->isJoinable())
			   {
               subject = thread;
               
               break; //for
			   }
		   }
      }
      
      if(subject != nullref)
         subject->join();
	}
	while(!threadList->isEmpty());
}

void ThreadLibrary::insert(RThread thread)
{
   sync_lock(mutex)
   {
	   threadList->addElement(thread);
      
      listChanged = true;
      
      mutex->notify();
   }
}

void ThreadLibrary::remove(RThread thread)
{
   sync_lock(mutex)
	{
      auto itr = threadList->iterator();
      
	   while(itr->hasNext())
	   {
		   if (itr->next()->id == thread->id)
		   {
			   itr->remove();
            
            listChanged = true;
            
			   break;
		   }
	   }
      
      mutex->notify();
   }
}

RThread ThreadLibrary::get(std::thread::id id)
{
	sync_lock(mutex)
	{
	   for(auto thread : threadList->iterator())
	   {
		   if(thread->st.get_id() == id)
		   {
			   return thread;
		   }
	   }
   }
   
	return nullref;
}

void ThreadLibrary::waitForAllThreads()
{
   getThreadLibrary().joinAllThreads();
}

ThreadLibrary& ThreadLibrary::getThreadLibrary()
{
	static ThreadLibrary lib;
	
	return lib;
}

} /* namespace aro */
