#ifndef WYEVERN_JOB_INCLUDED
#define WYEVERN_JOB_INCLUDED

namespace Wyevern::Jobs {
	struct Job {
		virtual ~Job() = default;

		virtual void Execute() = 0;
	};
}

#endif
