#pragma once

#include <commands/command.h>

class CmdStatus final : public Command
{
public:    
    explicit CmdStatus();

private:    
    void execute(class Interpreter& interpreter, std::vector<std::string>& args) const override;
};