#include <commands/quit.h>
#include <interpreter.h>

CmdQuit::CmdQuit()
: Command({"quit", "q"}, "Close the program")
{
}

void CmdQuit::execute(class Interpreter& interpreter, std::vector<std::string>& args) const
{
    interpreter.request_exit();
}