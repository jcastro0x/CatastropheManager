// Copyright (c) 2020-2021 Javier Castro - jcastro0x@gmail.com.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

#include <commands/help.h>
#include <interpreter.h>

#include <iostream>
#include <iomanip>
#include <algorithm>

CmdHelp::CmdHelp()
: Command({"help", "h", "?"}, "Print available commands", R"(
If this program is executed without params, print all available commands with
minor information (first name and short description).

If is called with one parameter, this will be threated as command name, printing
a more extensive information like name, aliases, description and, if has, a how-to-use.

The name can be the long name or any of its alias.

Example:
help ?
? ?
h ?
    )")
{
}

void CmdHelp::execute(Interpreter& interpreter, ArgsVector args) const
{
    // print all commands
    if(args.size() == 0)
    {
        for(const auto& cmd : interpreter.getCommands())
        {
            printCommandInfo(cmd.get());
        }
    }
    // print help about specific command
    else
    {
        auto[success, cmd] = findCommand(args[0], interpreter);
        if(success)
        {
            printFullCommandInfo(cmd);
        }
    }

    std::cout << std::flush;
}

std::pair<bool,Command*> CmdHelp::findCommand(std::string InName, Interpreter& interpreter) const
{
    std::transform(InName.begin(), InName.end(), InName.begin(), std::towlower);
    for(const auto& cmd : interpreter.getCommands())
    {
        auto names        = cmd->getNames();
        for(size_t i = 0; i < names.size(); i++)
        {
            std::transform(names[i].begin(), names[i].end(), names[i].begin(), std::towlower);
            if(names[i] == InName) 
            {
                return std::make_pair<bool,Command*>(true, cmd.get());
            }
        }
    }
    return std::make_pair<bool,Command*>(false, nullptr);
}

void CmdHelp::printCommandInfo(Command* command) const
{
    constexpr std::size_t width { 70 };

    const auto& name        = command->getName();
    const auto& description = command->getDescription();
    
    std::cout   << "[\033[31m" << name << "\033[0m]"
                << std::setw(std::min<size_t>(width, width-name.size())) << std::setfill('.')
                << description
                << std::endl;
}

void CmdHelp::printFullCommandInfo(Command* command) const
{
    const auto& name        = command->getName();
    const auto& description = command->getDescription();
    const auto& howtouse    = command->getHowToUse();
    
    std::cout << "[\033[31m" << name << "\033[0m] "
              << "( ";
    const auto& names = command->getNames();
    for(size_t i = 0; i < names.size(); i++)
    {
        std::cout << names[i] << " ";
    }
    std::cout << ")\n";

    std::cout << description << "\n\n";

    std::cout << "[\033[32mHow to Use\033[0m]";
    std::cout << howtouse << "\n" << std::endl;
}
