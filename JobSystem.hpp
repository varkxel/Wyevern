#ifndef VEXGINE_JOBSYSTEM_INCLUDED
#define VEXGINE_JOBSYSTEM_INCLUDED

#include <atomic>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <type_traits>

namespace VEXGINE::JobSystem
{
	class Job
	{
		friend class Instance;
		
	protected:
		virtual void Execute() = 0;
		
	private:
		std::atomic_bool complete { false };
	public:
		bool IsComplete() { return complete.load(); }
	};
	
	class Instance final
	{
		struct JobQueue final
		{
			std::atomic_bool processing { false };
			
			std::deque<std::shared_ptr<Job>> queue;
			std::mutex queueMutex;
			
			template<bool immediate = false>
			void Push(std::shared_ptr<Job> job)
			{
				std::scoped_lock lock(queueMutex);
				
				if constexpr(immediate) queue.push_front(job);
				else queue.push_back(job);
			}
			
			bool Pop(std::shared_ptr<Job>& result);
		};
		
	public:
		explicit Instance(unsigned maxThreads = ~0u);
		
	private:
		void WorkerThread();
		
	public:
		template<typename JobClass>
		std::shared_ptr<Job> Schedule()
		{
			static_assert
			(
				std::is_base_of<Job, JobClass>::value,
				"Only types deriving from VEXGINE::JobSystem::Job can be Scheduled by the job system."
			);
			std::shared_ptr<Job> job = std::make_shared(new JobClass);
			
			return job;
		}
		
	private:
		std::unique_ptr<JobQueue[]> threadQueues;
		
		unsigned threads;
	public:
		unsigned Threads() { return threads; }
	};
}

#endif