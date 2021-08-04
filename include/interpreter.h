#pragma once

#include <commands/command.h>
#include <options.h>
#include <memory_manager.h>

#include <memory>

class Interpreter final
{
public:
    explicit Interpreter(int argc, char** argv);
    void run();
    void request_exit();

    void printCommands() const;

private:
    std::vector<std::unique_ptr<Command>>   m_commands      {       };
    MemoryManager                           m_memoryManager {       };
    Options                                 m_options                ;
    bool                                    m_bRunning      { false };
};