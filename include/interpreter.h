#pragma once

#include <command.h>
#include <options.h>
#include <memory_manager.h>


class Interpreter final
{
public:
    explicit Interpreter(int argc, char** argv);
    void run();
    void request_exit();

    void printCommands() const;

private:
    std::vector<Command> m_commands     { };
    MemoryManager m_memoryManager       { };
    Options m_options                   { };
    bool m_bRunning                     { false };
};