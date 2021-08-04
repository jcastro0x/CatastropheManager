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

#pragma once

#include <cstdint>
#include <stack>
#include <memory>
#include <limits>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

enum class ECatastrophes : std::uint8_t
{
    None,           // All is quite and peacefully

    Storm,          // The skies throw insane rain and rays to the people
    Earthquake,     // The gods strike the earth with strenght
    Volcano,        // The tears of earth gods, bathe the earth
    Flood,          // God breaks his promise and try to drown us again
    WorldWar,       // Some day has to happen
    AlienAttack,    // Anunakis, Reptilians and all other terrorific aliens attack us
    Godzilla,       // Why not?
    Gantz,          // Black sphere

    COUNT
};

class MemoryManager final
{
    typedef boost::interprocess::allocator<ECatastrophes, boost::interprocess::managed_shared_memory::segment_manager> Allocator;
    typedef std::vector<ECatastrophes, Allocator> CatastrophesVector;

    static constexpr const char* SharedMemory_UUID  { "CatastropheUUID"                 };    // Indentifier used to Shared Memory
    static constexpr const char* Vector_UUID        { "VectorUUID"                      };    // Indentifier used to Vector allocated into Shared Memory
    static constexpr std::size_t MemoryAllocated    { std::numeric_limits<int>::max()   };    // How much memory used when allocated the shared memoryç


public:
    explicit MemoryManager();
    ~MemoryManager();

    void createSharedMemory();
    void openSharedMemory();

    void pushCastastrophe(ECatastrophes catastrophe);
    void pullCastastrophe() noexcept;

    [[nodiscard]] ECatastrophes getActiveCastastrophe() const noexcept;
    [[nodiscard]] bool hasAnyCastastrophe() const noexcept;
    [[nodiscard]] std::string getCastastropheName(ECatastrophes catastrophe) const;

private:
    std::stack<ECatastrophes> m_activeCastastrophes;
    std::unique_ptr<boost::interprocess::managed_shared_memory> m_segment;

    inline static const char* CastastrophesNames[] = {
        "None",
        "Storm",
        "Earthquake",
        "Volcano",
        "Flood",
        "WorldWar",
        "AlienAttack",
        "Godzilla",
        "Gantz"
    };

};
