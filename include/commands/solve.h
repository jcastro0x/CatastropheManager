#include <command.h>

class CmdSolve final : Command
{
    explicit CmdSolve();
    bool execute(class Interpreter& interpreter, const std::string& input) const override;
};