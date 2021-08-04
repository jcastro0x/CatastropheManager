#include "interpreter.h"
#include <command.h>

#include <iostream>
#include <algorithm>

Interpreter::Interpreter(int argc, char** argv)
: m_options(argc, argv)
{
    // std::vector<Command> innerCommands = {
    //     Command({"q", "quit"}, "Close the program", [](auto& interpreter, auto& args){
    //         interpreter.request_exit();
    //     })
    // };
    // m_commands.insert(m_commands.begin(), innerCommands.begin(), innerCommands.end());

    if(m_options.get_runAs() == EMode::Generator)
    {
        std::cout << "Run As Generator\n";
    }
    else
    {
        std::cout << "Run As Solver\n";
    }
}

void Interpreter::run()
{
    m_bRunning = true;

    std ::string line;
    while(m_bRunning && std::getline(std::cin, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), std::towlower);
        for(auto& cmd : m_commands)
        {
            if(cmd.execute(*this, line)) break;
        }
    }
}

void Interpreter::request_exit()
{
    m_bRunning = false;
}

void Interpreter::printCommands() const 
{
    for(auto& cmd : m_commands)
    {
        std::cout << cmd.getName() << "\n";
    }
    std::cout << std::flush;
}