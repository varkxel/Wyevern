#ifndef WYEVERN_JOBSYSTEM_INCLUDED
#define WYEVERN_JOBSYSTEM_INCLUDED

#include "Job.hpp"

#include <any>
#include <new>
#include <functional>
#include <thread>
#include <optional>
#include <vector>

namespace Wyevern
{
	class JobSystem final
	{
	public:
		struct
			alignas(std::hardware_constructive_interference_size)
			JobHandle
		{
			/// <summary>
			/// The job which is this job's parent.
			/// </summary>
			std::optional<std::shared_ptr<JobHandle>> parent;

			/// <summary>
			/// The amount of unfinished children this job has.
			/// </summary>
			std::atomic_int children;

			/// <summary>
			/// Job data/function pointer.
			/// </summary>
			std::unique_ptr<Job> data;
		};

		explicit JobSystem(unsigned threads = 0u);

		template<typename JobType>
		std::shared_ptr<JobHandle> Schedule(const JobType& job, std::optional<std::shared_ptr<JobHandle>> parent = std::nullopt)
		{
			std::shared_ptr<JobSystem::JobHandle> handle = std::make_shared<JobSystem::JobHandle>();
			if (parent.has_value())
			{
				++(parent.value()->children);
			}
			handle->parent = parent;
			handle->children = 0;
			handle->data = std::make_unique<JobType>(job);
			return handle;
		}

	private:
		/// <summary>
		/// Function that runs in each worker thread.
		/// </summary>
		static void WorkerThread();

		/// <summary>
		/// Total number of threads allocated to the JobSystem.
		/// </summary>
		unsigned threadCount;

		/// <summary>
		/// The thread definitions/handles.
		/// </summary>
		std::vector<std::thread> threads;
	};
}

#endif
