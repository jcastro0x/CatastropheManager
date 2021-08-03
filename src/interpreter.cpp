#include "interpreter.h"
#include "command.h"

#include <iostream>
#include <algorithm>

Interpreter::Interpreter(const std::vector<Command>& commands)
: m_commands(commands)
{
    std::vector<Command> innerCommands = {

        Command({"q", "quit"}, "Close the program", [](auto& args){
            std::exit(0);
        })
        
    };

    m_commands.insert(m_commands.begin(), innerCommands.begin(), innerCommands.end());
}

void Interpreter::run()
{
    m_bRunning = true;

    std ::string line;
    while(m_bRunning && std::getline(std::cin, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), std::towlower);
        std::cout << "Input: " << line << "\n";

        for(auto& cmd : m_commands)
        {
            if(cmd.execute(line)) break;
        }
    }
}

void Interpreter::printCommands() const 
{
    for(auto& cmd : m_commands)
    {
        std::cout << cmd.getName() << "\n";
    }
    std::cout << std::flush;
}