#include <commands/help.h>
#include <interpreter.h>

CmdHelp::CmdHelp()
: Command({"help", "h"}, "Print available commands")
{
}

void CmdHelp::execute(class Interpreter& interpreter, std::vector<std::string>& args) const
{
    interpreter.printCommands();
}