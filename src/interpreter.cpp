#include "interpreter.h"
#include "command.h"

#include <iostream>
#include <algorithm>

Interpreter::Interpreter(const std::vector<Command>& commands)
: m_commands(commands)
{
    std::vector<Command> innerCommands = {

        Command("q", [](){
            std::cout << "Close program\n";
            std::exit(0);
        }),
        Command("h", [this](){
            printCommands();
        })
    };

    m_commands.insert(m_commands.begin(), innerCommands.begin(), innerCommands.end());
}

void Interpreter::run()
{
    std ::string line;
    while(std::getline(std::cin, line))
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