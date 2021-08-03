#include <iostream>

#include <memory_manager.h>

#include "interpreter.h"
#include "options.h"


// TODO: Take a look
// https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp
// https://www.boost.org/doc/libs/1_71_0/doc/html/interprocess.html


int main(int argc, char** argv)
{
    options opt(argc, argv);
    if(opt.is_request_exit()) return EXIT_SUCCESS;
    opt.print_status();

    std::vector<Command> commands = {
        Command({"g", "generate"}, "Generate a castastrophe", [](auto& args){
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