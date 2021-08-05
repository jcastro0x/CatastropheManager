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
        std::cout << "Pushing " << getCastastropheName(catastrophe) << std::endl;
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
    auto vector = m_segment->find<CatastrophesVector>(Vector_UUID).first;
    if(vector == nullptr)
    {
        throw std::runtime_error("Can't find shared memory");
    }

    return vector;
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





