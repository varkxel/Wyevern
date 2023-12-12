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
		struct JobData
		{
			std::function<void()> function;
			std::optional<std::shared_ptr<JobData>> parent;

			/// <summary>
			/// The amount of unfinished children this job has.
			/// </summary>
			std::atomic_int children;

			alignas(std::hardware_constructive_interference_size)
			std::any data;
		};
		static void WorkerThread();

		unsigned threadCount;
		std::vector<std::thread> threads;
	};
}

#endif
