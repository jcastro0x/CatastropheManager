#pragma once

#include <cstdint>
#include <stack>
#include <memory>
#include <limits>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#ifdef NDEBUG
#include <iostream>
#endif

enum class ECatastrophes : std::uint8_t
{
    None,           // All is quite and peacefully

    Storm,          // The skies throw insane rain and rays to the people
    Earthquake,     // The gods strike the earth with strenght
    Volcano,        // The tears of earth gods, bathe the earth
    Flood,          // God breaks his promise and try to drown us again
    WorldWar,       // Some day has to happen
    AlienAttack,    // Anunakis, Reptilians and all other terrorific aliens attack us
    Godzilla,        // Why not?

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

    ECatastrophes getActiveCastastrophe() const noexcept;
    bool hasAnyCastastrophe() const noexcept;

    void pushCastastrophe(ECatastrophes catastrophe);
    void pullCastastrophe() noexcept;

    std::string getCastastropheName(ECatastrophes catastrophe) const;

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
        "Godzilla"   
    };

};
