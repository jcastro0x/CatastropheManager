#pragma once

#include <commands/command.h>

class CmdSolve final : public Command
{
public:    
    explicit CmdSolve();
    
private:
    void execute(class Interpreter& interpreter, std::vector<std::string>& args) const override;
};