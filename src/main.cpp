#include <interpreter.h>

int main(int argc, char** argv)
{
    try
    {
        Interpreter interpreter(argc, argv);
        interpreter.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}