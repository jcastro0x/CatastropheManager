#include <command.h>

class CmdGenerate final : Command
{
    explicit CmdGenerate();
    bool execute(class Interpreter& interpreter, const std::string& input) const override;
};