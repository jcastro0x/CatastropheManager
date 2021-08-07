// Copyright (c) 2020-2021 Javier Castro - jcastro0x@gmail.com.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

#include <memory_manager.h>
#include <log.h>
#include <boost/format.hpp>

#include <iostream>
#include <vector>

using namespace boost::interprocess;


MemoryManager::MemoryManager() 
{
}

MemoryManager::~MemoryManager() 
{
}

void MemoryManager::createSharedMemory()
{
    // Remove possibly old created shared memory
    shared_memory_object::remove(SharedMemory_UUID); //TODO: Move this to ctor?

    m_segment = std::make_unique<managed_shared_memory>(
        create_only, SharedMemory_UUID, MemoryAllocated
    );

    m_segment
    ->construct<CatastrophesVector>(Vector_UUID)(m_segment->get_segment_manager());

    //TODO: Maybe rename to storeSharedMemoryPointer?
    openSharedMemory();
}

void MemoryManager::openSharedMemory()
{
    if(!m_segment)
    {
        m_segment = std::make_unique<managed_shared_memory>(open_only, SharedMemory_UUID);
    }

    if(!m_CatastrophesVector)
    {
        m_CatastrophesVector = m_segment->find<CatastrophesVector>(Vector_UUID).first;
    }
}

void MemoryManager::destroySharedMemory()
{
    m_segment->destroy<CatastrophesVector>(Vector_UUID);
    m_CatastrophesVector = nullptr;
}

ECatastrophes MemoryManager::getActiveCastastrophe() const noexcept
{
    const auto vector = getCatastrophesVector();
    if(vector->size() != 0)
    {
        return (*vector)[0];
    }

    return ECatastrophes::None;
}

bool MemoryManager::hasAnyCastastrophe() const noexcept
{
    return getActiveCastastrophe() != ECatastrophes::None;
}

void MemoryManager::pushCastastrophe(const ECatastrophes catastrophe) 
{
    try
    {
        Log::log( (boost::format("Pushing %1%") % getCastastropheName(catastrophe)).str().c_str() );
        auto vector = getCatastrophesVector();
        vector->emplace_back(catastrophe);    
    }
    catch(const std::exception& e)
    {
        std::cerr << "Can't push" << getCastastropheName(catastrophe) << std::endl;
        std::cerr << e.what() << '\n';
    }
}

void MemoryManager::pullCastastrophe() noexcept
{

}

const MemoryManager::CatastrophesVector* MemoryManager::getCatastrophesVector() const
{
    if(!m_CatastrophesVector)
    {
        throw std::runtime_error("CatastrophesVector uninitilialized");
    }
    else
    {
        return m_CatastrophesVector;
    }
}

MemoryManager::CatastrophesVector* MemoryManager::getCatastrophesVector()
{
    const auto v = const_cast<const MemoryManager*>(this)->getCatastrophesVector();
    return const_cast<CatastrophesVector*>(v);
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

ECatastrophes MemoryManager::getCastastrophe(std::string_view name) const
{
    for(int i = 0; i < static_cast<int>(ECatastrophes::COUNT); i++)
    {
        if(CastastrophesNames[i] == name)
        {
            return static_cast<ECatastrophes>(i);
        }
    }

    return ECatastrophes::None;
}
