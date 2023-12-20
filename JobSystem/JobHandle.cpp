#include "JobHandle.hpp"

#include <algorithm>

using namespace Wyevern::Jobs;

void JobHandle::DataContainer::CopyOpImpl(const JobHandle::DataContainer& src, JobHandle::DataContainer& dest)
{
	std::copy(std::begin(src.data), std::end(src.data), std::begin(dest.data));
}

JobHandle::DataContainer::DataContainer()
{
}

JobHandle::DataContainer::DataContainer(const DataContainer& other)
{
	CopyOpImpl(other, *this);
}

JobHandle::DataContainer& JobHandle::DataContainer::operator=(const DataContainer& other)
{
	CopyOpImpl(other, *this);
	return *this;
}

JobHandle::JobHandle():
	unfinished(0),
	parent(std::nullopt)
{

}

JobHandle::JobHandle(const JobHandle& other):
	data(other.data),
	unfinished(other.unfinished.load(std::memory_order_seq_cst)),
	parent(other.parent)
{

}

JobHandle& JobHandle::operator=(const JobHandle& other)
{
	this->data = other.data;
	this->unfinished.exchange(other.unfinished.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
	this->parent = other.parent;
	return *this;
}
