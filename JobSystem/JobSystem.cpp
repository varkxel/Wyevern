#include "JobSystem.hpp"

#include <thread>

using namespace Wyevern;

JobSystem::JobSystem(unsigned threads)
{
	const unsigned coreCount = std::thread::hardware_concurrency();
	
	// Target the amount of cores minus 1, as main thread will become a worker thread too.
	const unsigned targetThreads = std::max(1u, coreCount - 1);
	
	// Cap the thread count to the max threads given, if it is given.
	threads = (threads > 0) ? std::min(targetThreads, threads) : targetThreads;
	
	for(unsigned threadID = 0; threadID < threads; ++threadID)
	{
	
	}
}

int main()
{

}
