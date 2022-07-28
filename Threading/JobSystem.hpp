#ifndef VEXGINE_JOBSYSTEM_INCLUDED
#define VEXGINE_JOBSYSTEM_INCLUDED

#include <functional>

namespace VEXGINE::Threading
{
	namespace JobSystem
	{
		unsigned int Threads();

		void Initialise();
		void Execute(const std::function<void()>& job);
	}
}

#endif