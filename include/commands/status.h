#include <command.h>

class CmdStatus final : Command
{
    explicit CmdStatus();
    bool execute(class Interpreter& interpreter, const std::string& input) const override;
};