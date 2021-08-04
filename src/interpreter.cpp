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

    std::cout << "\033[2J"; // clear screen
    if(m_options.get_runAs() == EMode::Generator)
    {
        std::cout << generator_title << std::endl;
        m_commands.emplace_back(std::make_unique<CmdGenerate>());
    }
    else
    {
        std::cout << solver_title << std::endl;
        m_commands.emplace_back(std::make_unique<CmdSolve>());
    }

    std::cout << "\033[32mWrite 'help' to print help\033[0m\n";
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