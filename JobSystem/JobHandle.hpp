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

		union DataContainer
		{
			friend struct JobHandle;
		private:
			static constexpr auto Size = Wyevern::Architecture::FalseSharingMitigation
				- sizeof(std::optional<std::shared_ptr<JobHandle>>)
				- sizeof(std::atomic_int);

			std::unique_ptr<Job> reference;
			std::array<std::byte, Size> data;
		public:
			template<typename JobType>
			explicit DataContainer(const JobType& job)
			{
				
			}
		};
		DataContainer data;
	};
}

#endif
