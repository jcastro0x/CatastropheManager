#include <iostream>

#include <memory_manager.h>

#include "interpreter.h"
#include "options.h"


int main(int argc, char** argv)
{
    const char* title = R"(
   ___|          |                    
 \___ \    _ \   | \ \   /  _ \   __| 
       |  (   |  |  \ \ /   __/  |    
 _____/  \___/  _|   \_/  \___| _|    
     ~catastrophe manager suite~
    )";
    std::cout << title << std::endl;


    options opt(argc, argv);
    if(opt.is_request_exit()) return EXIT_SUCCESS;
    opt.print_status();

    std::vector<Command> commands = {
        Command({"s", "solver"}, "Solve a castastrophe", [](auto& args){
            std::cout << "Solving... " << args[0] << "\n";
        })
    };

    std::cout << "Welcome to \033[31mCATASTROPHE SOLVER\033[0m suite\n";
    std::cout << "\033[36mPlease read README.MD from git repository to know how make fun things!\033[0m\n\n";
    {
        MemoryManager mm;
        mm.openSharedMemory();

        Interpreter Interpreter(commands);
        Interpreter.run();
    }
    std::cout << "Bye!" << std::endl;

    return EXIT_SUCCESS;
}