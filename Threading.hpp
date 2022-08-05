#ifndef VEXGINE_THREADING_INCLUDED
#define VEXGINE_THREADING_INCLUDED

#include <functional>
#include <shared_mutex>

namespace VEXGINE::Threading
{
	typedef std::function<void()> JobFunction;
	
	class Job
	{
	public:
		JobFunction function;
		
		void Await() const;
		bool HasCompleted() const;
		
		operator bool() const { return HasCompleted(); }
	private:
		bool completed = false;
		std::shared_mutex completedMutex;
		
		friend void CompleteJob(Job* job);
	};
	
	namespace JobSystem
	{
		unsigned int Threads();
		
		void Initialise();
		void Execute(Job* job);
		void ExecuteImmediate(Job* job);
	}
}

#endif