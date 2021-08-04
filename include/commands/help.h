#pragma once

#include <commands/command.h>

class CmdHelp final : public Command
{
public:    
    explicit CmdHelp();
    
private:
    void execute(class Interpreter& interpreter, std::vector<std::string>& args) const override;
};