#include "JobSystem.hpp"

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

using namespace VEXGINE::Threading;

namespace JobSystem
{
	void WorkerThread();
	
	unsigned int threadCount = 1u;
	
	std::mutex wakeMutex;
	std::condition_variable wakeCondition;
	std::deque<std::function<void()>> jobs;
	
	unsigned int Threads()
	{
		return threadCount;
	}
	
	void Initialise()
	{
		// Set total thread count
		unsigned int cpu_threads = std::thread::hardware_concurrency();
		threadCount = std::max(1u, cpu_threads);
		
		// Create the worker threads
		for(unsigned int threadID = 0; threadID < threadCount; ++threadID)
		{
			std::thread worker(WorkerThread);
			
			worker.detach();
		}
	}
	
	void WorkerThread()
	{
		std::function<void()> job;
		for(;;)
		{
			if((job = jobs.front())) job();
			else
			{
				std::unique_lock<std::mutex> lock(wakeMutex);
				wakeCondition.wait(lock);
			}
		}
	}
}
