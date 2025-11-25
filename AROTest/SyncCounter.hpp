#pragma once

#include <aro/core.hpp>

using namespace aro;

class SyncCounter;
typedef Ref<SyncCounter> RSyncCounter;

class SyncCounter :  public Object
{
	public:
		virtual void increment();

		virtual vint getCount();
	
	private:
		vint count = 0;
};

class Runner : public Thread
{
	public:
		Runner(RSyncCounter count);

		virtual void run();
	
	private:
		RSyncCounter counter;
};
