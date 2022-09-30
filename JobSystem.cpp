#include "JobSystem.hpp"

#include <algorithm>
#include <memory>
#include <thread>

using namespace VEXGINE::JobSystem;

void WorkerThread(unsigned threadID)
{
	
}

Instance::Instance(unsigned maxThreads)
{
	// maxThreads > 1
	maxThreads = std::max(1u, maxThreads);
	
	// Calculate the amount of threads to actually spawn (no more than physical cores minus main thread)
	const unsigned cores = std::thread::hardware_concurrency();
	threads = std::min(maxThreads, std::max(1u, cores - 1));
	
	// Initialise the thread queues
	threadQueues = std::make_unique<JobQueue[]>(threads);
	
	for(unsigned thread = 0; thread < threads; ++thread)
	{
		std::thread worker([thread]
		{
			WorkerThread(thread);
		});
	}
}

Instance::~Instance()
{
	// Tell all worker threads to quit/complete themselves.
	state->alive.store(false);
	state->awake.notify_all();
	
	// Wait
	for(unsigned i = 0; i < threads; ++i)
	{
		while(threadQueues[i].processing.load()) std::this_thread::yield();
	}
}

bool Instance::JobQueue::Pop(std::shared_ptr<Job>& result)
{
	std::scoped_lock lock(queueMutex);
	
	if(queue.empty())
	{
		processing.store(false);
		return false;
	}
	
	result = std::move(queue.front());
	queue.pop_front();
	processing.store(true);
	return true;
}
