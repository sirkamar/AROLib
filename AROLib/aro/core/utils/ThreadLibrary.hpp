#ifndef CORE_THREADLIBRARY_H
#define CORE_THREADLIBRARY_H

#include <aro/core/Thread.hpp>
#include <aro/core/impl/Array2D-impl.hpp>
#include <aro/util/Vector.hpp>

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
