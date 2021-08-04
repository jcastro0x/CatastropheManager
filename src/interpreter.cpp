#include <interpreter.h>
#include <commands.h>

#include <iostream>
#include <iomanip>
#include <algorithm>

Interpreter::Interpreter(int argc, char** argv)
: m_options(argc, argv)
{
    m_commands.emplace_back(std::make_unique<CmdQuit>());
    m_commands.emplace_back(std::make_unique<CmdHelp>());
    m_commands.emplace_back(std::make_unique<CmdStatus>());

    if(m_options.get_runAs() == EMode::Generator)
    {
        std::cout << "Run As Generator\n";
        m_commands.emplace_back(std::make_unique<CmdGenerate>());
    }
    else
    {
        std::cout << "Run As Solver\n";
        m_commands.emplace_back(std::make_unique<CmdSolve>());
    }
}

void Interpreter::run()
{
    m_bRunning = true;

    std::string line;
    bool bLastCommandExecuted = false;
    while(m_bRunning && std::getline(std::cin, line))
    {
        bLastCommandExecuted = false;
        std::transform(line.begin(), line.end(), line.begin(), std::towlower);
        
        for(auto& cmd : m_commands)
        {
            if(cmd->check(*this, line))
            {
                bLastCommandExecuted = true;
                break;
            }
        }

        if(!bLastCommandExecuted){
            std::cerr << "\033[31mCommand [" << line << "] not found\033[0m\n";
        }
    }
}

void Interpreter::request_exit()
{
    std::cout << "Exit requested\n";
    m_bRunning = false;
}

void Interpreter::printCommands() const 
{
    for(auto& cmd : m_commands)
    {
        constexpr std::size_t width { 70 };
        const auto& name        = cmd->getName();
        const auto& description = cmd->getDescription();
        
        std::cout   << "[\033[31m" << name << "\033[0m]"
                    << std::setw(std::min<size_t>(9999999, width-name.size())) << std::setfill('.')
                    << description
                    << "\n";
    }
    std::cout << std::flush;
}