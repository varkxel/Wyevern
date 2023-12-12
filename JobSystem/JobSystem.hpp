#ifndef WYEVERN_JOBSYSTEM_INCLUDED
#define WYEVERN_JOBSYSTEM_INCLUDED

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
		explicit JobSystem(unsigned threads = 0u);

	private:
		struct
			alignas(std::hardware_constructive_interference_size)
			JobData
		{
			/// <summary>
			/// The job function to call.
			/// </summary>
			std::function<void()> function;

			/// <summary>
			/// Job data stored here.
			/// </summary>
			std::any data;

			/// <summary>
			/// The job which is this job's parent.
			/// </summary>
			std::optional<std::shared_ptr<JobData>> parent;
			
			/// <summary>
			/// The amount of unfinished children this job has.
			/// </summary>
			std::atomic_int children;
		};
		static void WorkerThread();

		unsigned threadCount;
		std::vector<std::thread> threads;
	};
}

#endif
