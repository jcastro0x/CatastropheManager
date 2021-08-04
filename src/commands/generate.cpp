#include <commands/generate.h>

CmdGenerate::CmdGenerate()
: Command({"generate", "g"}, "Push a new catastrophe into shared memory")
{
}

void CmdGenerate::execute(class Interpreter& interpreter, std::vector<std::string>& args) const
{
}