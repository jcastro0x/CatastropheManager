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

public:
    [[nodiscard]] const std::vector<std::unique_ptr<Command>>& getCommands() const noexcept;
    [[nodiscard]] const MemoryManager& getMemoryManager() const noexcept;
    [[nodiscard]] MemoryManager& getMemoryManager() noexcept;
    [[nodiscard]] const Options& getOptions() const;

private:
    void update();



private:
    std::vector<std::unique_ptr<Command>>   m_commands      {       };
    MemoryManager                           m_memoryManager {       };
    std::shared_ptr<Options>                m_options       /* ctor*/;
    
    volatile bool                           m_bRunning      { false };

    inline static const char* generator_title = R"(
run as:        
___|                                 |                
|       _ \  __ \    _ \   __|  _` |  __|   _ \    __| 
|   |   __/  |   |   __/  |    (   |  |    (   |  |    
\____| \___| _|  _| \___| _|   \__,_| \__| \___/  _|  
            ~catastrophe manager suite~          
    )";

    inline static const char* solver_title = R"(
run as:
  ___|          |                    
\___ \    _ \   | \ \   /  _ \   __| 
      |  (   |  |  \ \ /   __/  |    
_____/  \___/  _|   \_/  \___| _|    
    ~catastrophe manager suite~
    )";    
};
