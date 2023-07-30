#ifndef WYEVERN_JOBSYSTEM_INCLUDED
#define WYEVERN_JOBSYSTEM_INCLUDED

namespace Wyevern
{
	class JobSystem
	{
	public:
		explicit JobSystem(unsigned threads = 0u);
	private:
		unsigned threads;
	};
}

#endif
