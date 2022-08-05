#include "Threading.hpp"

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

namespace VEXGINE::Threading
{
	inline void CompleteJob(Job* job)
	{
		std::unique_lock lock(job->completedMutex);
		job->completed = true;
	}
	
	bool Job::HasCompleted() const
	{
		std::shared_lock lock(completedMutex);
		return completed;
	}
	
	namespace JobSystem
	{
		unsigned int threadCount = 1u;
		
		std::mutex wakeMutex;
		std::condition_variable wakeCondition;
		
		std::deque<Job*> pool;
		std::mutex poolMutex;
		
		unsigned int Threads()
		{
			return threadCount;
		}
		
		void WorkerThread();
		
		inline void Poll()
		{
			wakeCondition.notify_one();
			std::this_thread::yield();
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
			for(;;)
			{
				poolMutex.lock();
					Job* job = pool.front();
					bool jobExists = (bool) job;
					
					if(jobExists) pool.pop_front();
				poolMutex.unlock();
				
				if(jobExists)
				{
					job->function();
					CompleteJob(job);
				}
				else
				{
					std::unique_lock<std::mutex> lock(wakeMutex);
					wakeCondition.wait(lock);
				}
			}
		}
		
		void Execute(Job* job)
		{
			poolMutex.lock();
				pool.push_back(job);
			poolMutex.unlock();
			
			wakeCondition.notify_one();
		}
		
		void ExecuteImmediate(Job* job)
		{
			poolMutex.lock();
				pool.push_front(job);
			poolMutex.unlock();
			
			wakeCondition.notify_one();
		}
	}
	
	void Job::Await() const
	{
		while(!HasCompleted()) JobSystem::Poll();
	}
}
