#include <commands/status.h>

CmdStatus::CmdStatus()
: Command({"status", "ss"}, "Check active catastrophes into shared memory")
{
}

void CmdStatus::execute(class Interpreter& interpreter, std::vector<std::string>& args) const
{
}