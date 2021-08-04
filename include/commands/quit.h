#pragma once

#include <commands/command.h>

class CmdQuit final : public Command
{
public:
    explicit CmdQuit();

private:
    void execute(class Interpreter& interpreter, std::vector<std::string>& args) const override;
};