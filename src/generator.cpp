#include <common.h>
#include <iostream>
#include "interpreter.h"

#include <boost/program_options.hpp>

// TODO: Take a look
// https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp
// https://www.boost.org/doc/libs/1_71_0/doc/html/interprocess.html

int foo(int argc, char** argv)
{
    float defaultRateSeconds = 0.0f;
    namespace po = boost::program_options;
    po::options_description generic("Generic options");
    generic.add_options()
    ("help,h",                                "produce help message")
    ("verbose,v",                             "print to stdout all kind of operations")
    ;

    po::options_description manag("Managment options");
    manag.add_options()
    ("automatic,a",                           "generate automatic catastrophes")
    ("automatic-rate,r",  po::value<float>(&defaultRateSeconds)->default_value(10.0f)
    , "seconds rate to generate automatic catastrophes")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, generic), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        std::cout << generic << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        std::cout << "Compression level was set to " 
     << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }

    return 0;
}

int main(int argc, char** argv)
{
    if(foo(argc, argv) == 1) return 1;


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

    std::cout << "Welcome to \033[31mCATASTROPHE GENERATOR\033[0m suite\n";
    std::cout << "Please read README.MD from git repository to know how make fun things!\n\n";
    {
        Interpreter Interpreter(commands);
        Interpreter.run();
    }
    std::cout << "Bye!" << std::endl;

    return EXIT_SUCCESS;
}