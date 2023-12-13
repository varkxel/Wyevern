#include "JobSystem.hpp"

#include <algorithm>

using namespace Wyevern::Jobs;

JobSystem::JobSystem(unsigned threadCount)
{
	const unsigned coreCount = std::thread::hardware_concurrency();
	
	// Target the amount of cores minus 1, as main thread will become a worker thread too.
	const unsigned targetThreads = std::max(1u, coreCount - 1);
	
	// Cap the thread count to the max threads given, if it is given.
	threadCount = (threadCount > 0) ? std::min(targetThreads, threadCount) : targetThreads;
	this->threadCount = threadCount;

	// Initialise the worker threads
	threads.reserve(this->threadCount);
	for(unsigned threadID = 0; threadID < this->threadCount; ++threadID)
	{
		threads.push_back(std::thread(WorkerThread));
		std::thread& thread = threads.back();
		thread.detach();
	}
}

void JobSystem::WorkerThread()
{
	while(true)
	{
		
	}
}
