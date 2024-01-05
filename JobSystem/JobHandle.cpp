#include "JobHandle.hpp"

using namespace Wyevern::Jobs;

JobHandle::DataContainer::DataContainer():
	data(std::array<std::byte, PaddingSize> {})
{
}

JobHandle::DataContainer::DataContainer(const DataContainer& other):
	data(other.data)
{
}

JobHandle::DataContainer& JobHandle::DataContainer::operator=(const DataContainer& other) {
	data = other.data;
	return *this;
}

JobHandle::JobHandle():
	unfinished(0),
	parent(std::nullopt)
{
}

JobHandle::JobHandle(const JobHandle& other):
	unfinished(other.unfinished.load(std::memory_order_seq_cst)),
	parent(other.parent),
	data(other.data)
{
}

JobHandle& JobHandle::operator=(const JobHandle& other) {
	this->data = other.data;
	this->unfinished.exchange(other.unfinished.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
	this->parent = other.parent;
	return *this;
}
