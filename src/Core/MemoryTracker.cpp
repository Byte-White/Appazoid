#include "MemoryTracker.h"
namespace az
{
	unsigned int MemoryTracker::total_allocations_count = 0;
	unsigned int MemoryTracker::total_deallocations_count = 0;
	unsigned int MemoryTracker::total_allocated_memory = 0;
	unsigned int MemoryTracker::total_deallocated_memory = 0;
	unsigned int MemoryTracker::allocated_memory = 0;
}

void* operator new(size_t size)
{
	void* ptr = malloc(size);
	az::MemoryTracker::total_allocations_count += 1;
	az::MemoryTracker::total_allocated_memory += size;
	az::MemoryTracker::allocated_memory += size;
	return ptr;
}

void operator delete(void* memory, size_t size)
{
	az::MemoryTracker::total_deallocations_count += 1;
	az::MemoryTracker::total_deallocated_memory += size;
	az::MemoryTracker::allocated_memory -= size;
	free(memory);
}