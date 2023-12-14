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
	struct JobHandle
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
			data = DataContainer(job);
		}

		/// <summary>
		/// The job which is this job's parent.
		/// </summary>
		std::optional<std::shared_ptr<JobHandle>> parent;

		/// <summary>
		/// The amount of unfinished children this job has, plus itself.
		/// </summary>
		std::atomic_llong unfinished;

		union DataContainer
		{
			friend struct JobHandle;
		private:
			static constexpr auto PaddingSize = Wyevern::Architecture::FalseSharingMitigation
				- sizeof(parent)
				- sizeof(unfinished);

			std::unique_ptr<Job> reference;
			std::array<std::byte, PaddingSize> data;
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
