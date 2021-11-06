#ifndef CORE_THREADLIBRARY_H
#define CORE_THREADLIBRARY_H

#include <aro/core/Thread.h>
#include <aro/core/Array2D-impl.h>
#include <aro/util/Vector.h>

int main(int argc, char **argv);

namespace aro {

class ThreadLibrary final
{
	RObject mutex;
   
   ThreadLibrary();
   
	friend class Thread;
   
   void joinAllThreads();
   
   vbool listChanged = false;
   
	void insert(RThread thread);
	
	void remove(RThread thread);
	
	RThread get(std::thread::id id);
   
   static void waitForAllThreads();
	
	util::RVector<Thread> threadList;
   
	static ThreadLibrary& getThreadLibrary();

	friend int ::main(int argc, char **argv);
};

} /* namespace aro */

#endif /* CORE_THREADLIBRARY_H */
