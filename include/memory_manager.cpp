#include "memory_manager.h"

#include <iostream>
#include <vector>

using namespace boost::interprocess;






MemoryManager::MemoryManager() 
{
}

MemoryManager::~MemoryManager() 
{
    std::cout << "Erasing shared memory";
    
    if(!shared_memory_object::remove(SharedMemory_UUID))
    {
        std::cerr << "Can't erase shared memory";
    }
}

void MemoryManager::createSharedMemory()
{
    shared_memory_object::remove(SharedMemory_UUID);

    m_segment = std::make_unique<managed_shared_memory>(create_only, SharedMemory_UUID, MemoryAllocated);

    Allocator alloc_inst(m_segment->get_segment_manager());
    CatastrophesVector* vector = m_segment->construct<CatastrophesVector>(Vector_UUID)(alloc_inst);

    std::cout << "Writing 100 elements\n";
    for(int i = 0; i < 100; i++)
    {
        vector->push_back(ECatastrophes::None);
    }
}

void MemoryManager::openSharedMemory()
{
    m_segment = std::make_unique<managed_shared_memory>(open_only, SharedMemory_UUID);
    CatastrophesVector* vector = m_segment->find<CatastrophesVector>(Vector_UUID).first;

    std::sort(vector->rbegin(), vector->rend());

    std::cout << "Reading 100 elements\n";
    for(int i = 0; i < 100; i++)
    {
        std::cout << getCastastropheName((*vector)[i]) << "\n";
    }

    m_segment->destroy<CatastrophesVector>(Vector_UUID);
}

ECatastrophes MemoryManager::getActiveCastastrophe() const noexcept
{
    return ECatastrophes::None;
}

bool MemoryManager::hasAnyCastastrophe() const noexcept
{
    return getActiveCastastrophe() != ECatastrophes::None;
}

void MemoryManager::pushCastastrophe(const ECatastrophes catastrophe) 
{
    std::cout << "Pushing " << getCastastropheName(catastrophe) << std::endl;
}

void MemoryManager::pullCastastrophe() noexcept
{

}

std::string MemoryManager::getCastastropheName(ECatastrophes catastrophe) const
{
    const int index = static_cast<int>(catastrophe);
    if(index < 0 || index >= static_cast<int>(ECatastrophes::COUNT))
    {
        throw std::runtime_error("Trying to access out-of-index catastrophe");
    }

    return CastastrophesNames[index];
}





