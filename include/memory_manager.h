#pragma once

#include <cstdint>
#include <stack>
#include <memory>

#include <boost/interprocess/managed_shared_memory.hpp>

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
    Godzilla        // Why not?
};

class MemoryManager final
{
    static constexpr const char* UUID               { "CatastropheUUID" };      // Indentifier used to Shared Memory
    static constexpr std::size_t MemoryAllocated    { INT_MAX };                   // How much memory used when allocated the shared memoryç


public:
    explicit MemoryManager();
    ~MemoryManager();

    void createSharedMemory();
    void openSharedMemory();

    ECatastrophes getActiveCastastrophe() const;

    bool hasAnyCastastrophe() const;
    void pushCastastrophe(ECatastrophes catastrophes);
    void pullCastastrophe() noexcept;


//~======================================================================
// DEBUG AND ERROR HELPERS
//~======================================================================
private:
    /***
     * @brief Helper function to print debug information (only available in no release builds)
     * @param args Variadic arguments to print
     */
    template<typename... Args>
    void debug(Args... args)
    {
    #ifdef NDEBUG
        std::cout << args... << std::endl;
    #endif
    }

    template<typename... Args>
    void error(Args... args)
    {
    #ifdef NDEBUG
        std::cerr << args... << std::endl;
    #endif
    }

private:
    std::stack<ECatastrophes> m_activeCastastrophes;
    std::unique_ptr<boost::interprocess::managed_shared_memory> m_segment;
};
