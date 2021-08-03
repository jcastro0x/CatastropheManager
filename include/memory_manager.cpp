#include "memory_manager.h"

#include <iostream>
#include <vector>

#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;

typedef allocator<int, managed_shared_memory::segment_manager> Allocator;
typedef std::vector<int, Allocator> SmVector;


MemoryManager::MemoryManager() 
{
    //shared_memory_object::remove(UUID);

    // shared_memory_object smo {create_only, UUID, read_write};
    // smo.truncate(MemoryAllocated);
    
    // if(smo.get_mode() == boost::interprocess::mode_t::read_only)
    // {
    //     error("Read Only shared memory");
    // }
    // else
    // {
    //     debug("Shared memory created successfully");    
    //     debug(smo.get_name());    
    //}


}

MemoryManager::~MemoryManager() 
{
    shared_memory_object::remove(UUID);
}

void MemoryManager::createSharedMemory()
{
    m_segment = std::make_unique<managed_shared_memory>(create_only, UUID, MemoryAllocated);

    Allocator alloc_inst(m_segment->get_segment_manager());
    SmVector* vector = m_segment->construct<SmVector>("SmVector")(alloc_inst);

    std::cout << "Writing 100 elements\n";
    for(int i = 0; i < 100; i++)
    {
        vector->push_back(i);
    }
}

void MemoryManager::openSharedMemory()
{
    m_segment = std::make_unique<managed_shared_memory>(open_only, UUID);
    SmVector* vector = m_segment->find<SmVector>("SmVector").first;

    std::sort(vector->rbegin(), vector->rend());

    std::cout << "Reading 100 elements\n";
    for(int i = 0; i < 100; i++)
    {
        std::cout << (*vector)[i] << "\n";
    }

    m_segment->destroy<SmVector>("SmVector");
}

ECatastrophes MemoryManager::getActiveCastastrophe() const 
{
    return ECatastrophes::None;
}

bool MemoryManager::hasAnyCastastrophe() const 
{
    return getActiveCastastrophe() != ECatastrophes::None;
}

void MemoryManager::pushCastastrophe(const ECatastrophes catastrophes) 
{

}

void MemoryManager::pullCastastrophe() noexcept
{

}






