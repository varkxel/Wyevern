#ifndef WYEVERN_JOBSYSTEM_INCLUDED
#define WYEVERN_JOBSYSTEM_INCLUDED

#include "Job.hpp"
#include "JobHandle.hpp"

#include <memory>
#include <optional>
#include <thread>
#include <vector>

namespace Wyevern::Jobs {
	class JobSystem final {
	public:
		explicit JobSystem(unsigned threadCount = 0u);

		template<typename JobType>
		std::shared_ptr<JobHandle> Schedule(
			const JobType& job,
			std::optional<std::shared_ptr<JobHandle>> parent = std::nullopt
		) {
			std::shared_ptr<JobHandle> handle = std::make_shared<JobHandle>(job, parent);
			
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
