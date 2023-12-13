#ifndef WYEVERN_JOBHANDLE_INCLUDED
#define WYEVERN_JOBHANDLE_INCLUDED

#include <atomic>
#include <memory>
#include <new>
#include <optional>

namespace Wyevern::Jobs
{
	struct
		// Prevent false sharing.
		// In the future, the data member should be padding storing job data.
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
}

#endif
