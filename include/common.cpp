#include "common.h"
#include <boost/interprocess/shared_memory_object.hpp>

using namespace boost::interprocess;


MemoryManager::MemoryManager() 
{
    shared_memory_object smo {open_or_create, UUID, read_write};
    smo.truncate(MemoryAllocated);
    
    if(smo.get_mode() == boost::interprocess::mode_t::read_only)
    {
        error("Read Only shared memory");
    }
    else
    {
        debug("Shared memory created successfully");    
        debug(smo.get_name());    
    }
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






