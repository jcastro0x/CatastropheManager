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
#include <log.h>

#include <iostream>
#include <algorithm>

#include <boost/format.hpp>
#include <thread>

Interpreter::Interpreter(int argc, char** argv)
: m_options(std::make_shared<Options>(argc, argv))
{
    m_bRunning = !m_options->is_request_exit();
    if(!m_bRunning) return;

    m_commands.emplace_back(std::make_unique<CmdQuit>());
    m_commands.emplace_back(std::make_unique<CmdHelp>());
    m_commands.emplace_back(std::make_unique<CmdOptions>());
    m_commands.emplace_back(std::make_unique<CmdStatus>());
    m_commands.emplace_back(std::make_unique<CmdClear>());
    m_commands.emplace_back(std::make_unique<CmdCatastrophesList>());

    Log::initialize(m_options);

    if(!m_options->is_no_clear())
    {
        Log::cls();
    }

    if(m_options->get_runAs() == EMode::Generator)
    {
        Log::print(generator_title);
        m_commands.emplace_back(std::make_unique<CmdGenerate>());
        
        getMemoryManager().createSharedMemory();
    }
    else
    {
        Log::print(solver_title);
        m_commands.emplace_back(std::make_unique<CmdSolve>());

        getMemoryManager().openSharedMemory();
    }

    Log::print("\033[32mWrite 'help' to print help\033[0m");
}

void Interpreter::run()
{
    std::thread tupdate(std::bind(&Interpreter::update, this));

    std::string line;
    bool bLastCommandExecuted = false;
    while(m_bRunning)
    {
        bLastCommandExecuted = false;

        // Print prompt
        if(m_bRunning){
            std::cout << "$: ";
        }

        std::getline(std::cin, line);
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

    // Wait to finish update thread
    tupdate.join();
}

void Interpreter::request_exit()
{
    Log::log("Exit requested");
    m_bRunning = false;
}

const std::vector<std::unique_ptr<Command>>& Interpreter::getCommands() const noexcept
{
    return m_commands;
}

const MemoryManager& Interpreter::getMemoryManager() const noexcept
{
    return m_memoryManager;
}

MemoryManager& Interpreter::getMemoryManager() noexcept
{
    const auto& mm = const_cast<const Interpreter*>(this)->getMemoryManager();
    return const_cast<MemoryManager&>(mm);
}

const Options& Interpreter::getOptions() const
{
    if(!m_options) throw std::runtime_error("getOptions called with invalid m_options class variable");
    return *m_options;
}

void Interpreter::update()
{
    using namespace std::chrono_literals;
    while(m_bRunning)
    {
        std::this_thread::sleep_for(500ms); //we don't want to drain all CPU!!

        //log((boost::format("first: %1%, second: %2%\n") % 10 % 22).str().c_str());
        //war((boost::format("first: %1%, second: %2%\n") % 33 % 44).str().c_str());
        //err((boost::format("first: %1%, second: %2%\n") % 55 % 66).str().c_str());
    }
}
