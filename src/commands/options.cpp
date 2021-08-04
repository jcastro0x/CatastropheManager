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

#include <commands/options.h>
#include <interpreter.h>

#include <iostream>

CmdOptions::CmdOptions()
: Command({"options", "o"}, "Print status options")
{
}

void CmdOptions::execute(Interpreter& interpreter, ArgsVector args) const
{
    const auto& options = interpreter.getOptions();

    auto BoolToString = [](bool b) constexpr {
        return b ? "True" : "False";
    };

    auto ModeToString = [](EMode m) constexpr {
        return m == EMode::Generator ? "Generator" : "Solver";
    };

    std::cout << "Program initialized with next parameters:\n";
    std::cout << "Verbose        : " << BoolToString(options.is_verbose())   << "\n";
    std::cout << "Automatic      : " << BoolToString(options.is_automatic()) << "\n";
    std::cout << "No-Clear       : " << BoolToString(options.is_no_clear())  << "\n";
    std::cout << "Run As         : " << ModeToString(options.get_runAs())    << "\n";
    std::cout << "Automatic Rate : " << options.get_automatic_rate()         << "\n";
}
