#ifndef WYEVERN_JOBSYSTEM_INCLUDED
#define WYEVERN_JOBSYSTEM_INCLUDED

#include <atomic>
#include <functional>
#include <memory>
#include <shared_mutex>

namespace Wyevern
{
	struct Job
	{
		virtual ~Job() = 0;
		
		virtual void Execute() = 0;
	};
	
	class JobSystem
	{
	private:
		struct Task
		{
			// Function to execute, provided with the job iteration index.
			std::function<void(int)> function;
			
			std::atomic_int* taskCounter;
		};
		
		struct JobQueue final
		{
			explicit JobQueue(long capacity);
			
			long capacity;
			std::unique_ptr<Task[]> tasks;
			std::shared_mutex resizeMutex;
			
			long back = 0;
			std::atomic_long front = { 0 };
			
			long Size();
			void Resize();
			
			void Push(const Task& task);
			bool Pop(Task& task);
		};
		
	public:
		explicit JobSystem(unsigned maxThreads = 0u);
		
	};
}

#endif