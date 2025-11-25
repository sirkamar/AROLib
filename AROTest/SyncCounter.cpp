#include "SyncCounter.hpp"

void SyncCounter::increment()
{
	//sync_lock(thisref)
	//{
	//	count++;
	//}
	count++;
}

vint SyncCounter::getCount()
{
	//sync_lock(thisref)
	//{
	//	return count;
	//}
	return count;
}

Runner::Runner(RSyncCounter count) : counter(count) {}

void Runner::run()
{
	for (vint i = 0; i < 1000; i++)
	{
		counter->increment();

		Thread::sleep(((vint)(Math::random() * 10)) + 1);
	}
}
