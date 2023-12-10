#ifndef WYEVERN_JOB_INCLUDED
#define WYEVERN_JOB_INCLUDED

namespace Wyevern
{
	struct Job
	{
		virtual void Execute() = 0;
	};
}

#endif
