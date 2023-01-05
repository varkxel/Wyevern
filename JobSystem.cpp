#include "JobSystem.hpp"

#include <functional>
#include <thread>
#include <stdexcept>

using namespace Wyevern;

JobSystem::JobSystem(const unsigned maxThreads)
{
	const unsigned cores = std::thread::hardware_concurrency();
	
	// Target the amount of cores minus 1, as main thread will become a worker thread too.
	const unsigned targetThreads = std::max(1u, cores - 1);
	
	// Cap the thread count to the max threads given, if it is given.
	const unsigned threads = (maxThreads > 0) ? std::min(targetThreads, maxThreads) : targetThreads;
}

JobSystem::JobQueue::JobQueue(long capacity)
{
	// Check for valid capacity size.
	// Must be power of 2 due to the capacity doubling once over capacity.
	#ifndef WYEVERN_STRIP_CHECKS
	if(capacity < 2 || (capacity % 2) != 0)
	{
		throw std::invalid_argument("Specified capacity \"" + std::to_string(capacity) + "\" is not a power of 2.");
	}
	#endif
	
	this->capacity = capacity;
	tasks = std::make_unique<Task[]>(capacity);
}

long JobSystem::JobQueue::Size() { return back - front.load(); }

void JobSystem::JobQueue::Resize()
{
	std::lock_guard lock(resizeMutex);
	
	std::unique_ptr<Task[]> oldArray = std::move(tasks);
	
	long oldCapacity = capacity;
	capacity *= capacity;
	
	back %= oldCapacity;
	long frontVal = front.load();
	frontVal %= oldCapacity;
	front.store(frontVal);
	
	tasks = std::make_unique<Task[]>(capacity);
	for(long i = 0; i < oldCapacity; i++) tasks[i] = oldArray[i];
}

void JobSystem::JobQueue::Push(const Task& task)
{
	std::shared_lock lock(resizeMutex);
	
	if(Size() >= capacity)
	{
		lock.unlock();
		Resize();
		lock.lock();
	}
	tasks[back++ % capacity] = task;
}

bool JobSystem::JobQueue::Pop(Task& task)
{
	std::shared_lock lock(resizeMutex, std::defer_lock);
	if(!lock.try_lock()) return false;
	
	if(Size() <= 0)
	{
		lock.unlock();
		return false;
	}
	
	task = tasks[--back % capacity];
	lock.unlock();
	return true;
}
