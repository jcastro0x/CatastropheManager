#include <command.h>

class CmdQuit final : Command
{
    explicit CmdQuit();
    bool execute(class Interpreter& interpreter, const std::string& input) const override;
};