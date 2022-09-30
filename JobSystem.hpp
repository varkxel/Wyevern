#ifndef VEXGINE_JOBSYSTEM_INCLUDED
#define VEXGINE_JOBSYSTEM_INCLUDED

#include <atomic>
#include <deque>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <type_traits>

namespace VEXGINE::JobSystem
{
	class Job
	{
		friend class Instance;
	public:
		// Job();
		virtual ~Job() = default;
		
	protected:
		/// This method is executed on the worker thread once the job is executed.
		virtual void Execute() = 0;
		
	private:
		/// Completion status variable for the Job.
		/// False while the job is not complete, True once the job is completed.
		std::atomic_bool complete { false };
	public:
		/// Returns true when the job has been completed.
		bool IsComplete() { return complete.load(); }
	};
	
	class Instance final
	{
	private:
		/// The per-thread job queue structure.
		/// Each worker thread has one queue, this structure is the queue object.
		struct JobQueue final
		{
			/// Processing state variable.
			/// True while there are worker threads acting on the job queue.
			std::atomic_bool processing { false };
			
			/// The job queue.
			std::deque<std::shared_ptr<Job>> queue;
			std::mutex queueMutex;
			
			template<bool immediate = false>
			void Push(const std::shared_ptr<Job>& job)
			{
				std::scoped_lock lock(queueMutex);
				
				// Push to front or back dependent of the value "immediate".
				if constexpr(immediate) queue.push_front(job);
				else queue.push_back(job);
			}
			
			bool Pop(std::shared_ptr<Job>& result);
		};
		
		/// The amount of threads assigned to the Job System.
		unsigned threads;
		
		/// The per-thread job queues.
		std::unique_ptr<JobQueue[]> threadQueues;
		std::atomic<unsigned> nextQueue { 0 };
		
		/// Worker thread-shared state.
		struct State final
		{
			/// Whether the Job System is active.
			/// Worker threads will terminate if set to false.
			std::atomic_bool alive { true };
			
			/// Condition to wake up a worker thread.
			std::condition_variable awake;
			std::mutex awakeMutex;
		};
		std::shared_ptr<State> state = std::make_shared<State>();
	public:
		explicit Instance(unsigned maxThreads = ~0u);
		~Instance();
		
		/// Returns the amount of threads assigned to the Job System.
		[[nodiscard]] unsigned Threads() const { return threads; }
		
		template<typename JobClass>
		std::shared_ptr<Job> Schedule()
		{
			// Check that the job is actually executable.
			static_assert
			(
				std::is_base_of<Job, JobClass>::value,
				"Only types deriving from VEXGINE::JobSystem::Job can be Scheduled by the job system."
			);
			
			// Create job instance and add it to the work queue.
			std::shared_ptr<Job> job = std::make_shared(new JobClass);
			const unsigned queue = nextQueue.fetch_add(1) % threads;
			threadQueues[queue].Push(job);
			
			// Wake up a worker thread.
			state->awake.notify_one();
			
			return job;
		}
	};
}

#endif