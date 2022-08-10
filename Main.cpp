#include "Threading.hpp"

#include <iostream>

int main()
{
	using namespace VEXGINE::Threading;
	
	Job testJob = (Job) [] { std::cout << "piss" << std::endl; };
	JobSystem::Execute(&testJob);
	testJob.Await();
	
	return 0;
}