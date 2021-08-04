#pragma once

#include <commands/command.h>

class CmdGenerate final : public Command
{
public:
    explicit CmdGenerate();

private:
    void execute(class Interpreter& interpreter, std::vector<std::string>& args) const override;
};