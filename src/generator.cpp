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

#include <iostream>

#include <memory_manager.h>

#include <interpreter.h>
#include <options.h>


// TODO: Take a look
// https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp

int main(int argc, char** argv)
{
    const char* title = R"(
   ___|                                 |                
  |       _ \  __ \    _ \   __|  _` |  __|   _ \    __| 
  |   |   __/  |   |   __/  |    (   |  |    (   |  |    
 \____| \___| _|  _| \___| _|   \__,_| \__| \___/  _|  
              ~catastrophe manager suite~          
    )";
    std::cout << title << std::endl;

    options opt(argc, argv);
    if(opt.is_request_exit()) return EXIT_SUCCESS;
    opt.print_status();

    std::vector<Command> commands = {
        Command({"g", "generate"}, "Generate a castastrophe", [](auto& interpreter, auto& args){
            std::cout << "Generating... " << args[0] << "\n";
        })
    };

    std::cout << "Welcome to \033[31mCATASTROPHE GENERATOR\033[0m suite\n";
    std::cout << "\033[36mPlease read README.MD from git repository to know how make fun things!\033[0m\n\n";
    {
        MemoryManager mm;
        mm.createSharedMemory();

        Interpreter Interpreter(commands);
        Interpreter.run();
    }
    std::cout << "Bye!" << std::endl;

    return EXIT_SUCCESS;
}