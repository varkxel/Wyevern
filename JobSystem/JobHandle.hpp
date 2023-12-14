#ifndef WYEVERN_JOBHANDLE_INCLUDED
#define WYEVERN_JOBHANDLE_INCLUDED

#include "Global/Architecture.hpp"

#include "Job.hpp"

#include <atomic>
#include <array>
#include <memory>
#include <optional>

namespace Wyevern::Jobs
{
	struct
		// Prevent false sharing.
		JobHandle
	{
	public:
		template<typename JobType>
		JobHandle(const JobType& job, std::optional<std::shared_ptr<JobHandle>> parent = std::nullopt)
		{
			this->unfinished = 1;
			if (parent.has_value())
			{
				++(parent.value()->unfinished);
			}
			this->parent = parent;
			this->job.dataPtr = std::make_unique<Job>(job);
		}

		/// <summary>
		/// The job which is this job's parent.
		/// </summary>
		std::optional<std::shared_ptr<JobHandle>> parent;

		/// <summary>
		/// The amount of unfinished children this job has, plus itself.
		/// </summary>
		std::atomic_int unfinished;

		/// <summary>
		/// Job data/function pointer.
		/// </summary>
		union
		{
			friend struct JobHandle;
		private:
			std::unique_ptr<Job> dataPtr;
			std::array<
				std::byte,
				Wyevern::Architecture::FalseSharingMitigation
					- sizeof(std::optional<std::shared_ptr<JobHandle>>)
					- sizeof(std::atomic_int)
			> data;
		}
		job;
	};
}

#endif
