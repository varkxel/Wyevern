#include "JobSystem.hpp"

#include <algorithm>
#include <thread>

using namespace VEXGINE::JobSystem;

Instance::Instance(unsigned maxThreads)
{
	// maxThreads > 1
	maxThreads = std::max(1u, maxThreads);
	
	// Calculate the amount of threads to actually spawn (no more than physical cores minus main thread)
	const unsigned cores = std::thread::hardware_concurrency();
	threads = std::min(maxThreads, std::max(1u, cores - 1));
	
	// Initialise the thread queues
	threadQueues.reset(new JobQueue[threads]);
	
	
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
