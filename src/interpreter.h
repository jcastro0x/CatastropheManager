#pragma once

#include "command.h"
#include <memory_manager.h>


class Interpreter final
{
public:
    explicit Interpreter(const std::vector<Command>& commands);
    void run();

    void printCommands() const;

private:
    std::vector<Command> m_commands     { };
    MemoryManager m_memoryManager       { };
};