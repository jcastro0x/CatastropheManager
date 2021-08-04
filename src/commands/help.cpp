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

CmdHelp::CmdHelp()
: Command({"help", "h", "?"}, "Print available commands")
{
}

void CmdHelp::execute(class Interpreter& interpreter, std::vector<std::string>& args) const
{
    for(const auto& cmd : interpreter.getCommands())
    {
        constexpr std::size_t width { 70 };
        const auto& name        = cmd->getName();
        const auto& description = cmd->getDescription();
        
        std::cout   << "[\033[31m" << name << "\033[0m]"
                    << std::setw(std::min<size_t>(0, width-name.size())) << std::setfill('.')
                    << description
                    << "\n";
    }
    std::cout << std::flush;
}