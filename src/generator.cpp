#include <common.h>
#include <iostream>
#include "interpreter.h"

int main(int argc, char** argv)
{
    std::vector<Command> commands = {

        Command("q", [](){
            std::cout << "Close program\n";
            std::exit(0);
        }),
        Command("execute", [](){
            std::cout << "Close program\n";
            std::exit(0);
        })
    };

    std::cout << "Creating Memory Manager...\n";
    {
        Interpreter Interpreter(commands);
    }
    std::cout << "Finish..." << std::endl;

    return EXIT_SUCCESS;
}