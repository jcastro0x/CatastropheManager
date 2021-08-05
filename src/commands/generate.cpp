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

#include <commands/generate.h>
#include <interpreter.h>
#include <memory_manager.h>

#include <algorithm>
#include <iostream>

CmdGenerate::CmdGenerate()
: Command({"generate", "g"}, "Push a new catastrophe into shared memory", R"(
Need at leat one param.
The program iterate over all params and treat them as names of possible castastrophes.
For each catastrophe, 'generate' push them into shared memory.

The params are case insentive.

Example:
generate gantz storm volcano
    )")
{
}

void CmdGenerate::execute(Interpreter& interpreter, ArgsVector args) const
{
    if(args.size() < 1)
    {
        std::cerr << "Error arguments" << std::endl;
        return;
    }

    auto& mm = interpreter.getMemoryManager();

    std::string catastropheName;
    for(size_t i = 0; i < args.size(); i++)
    {
        catastropheName = args[i];
        std::transform(catastropheName.begin(), catastropheName.end(), 
                       catastropheName.begin(), std::towlower);
        catastropheName[0] -= 32; //toupper first character

        ECatastrophes catastrophe = mm.getCastastrophe(catastropheName);
        if(catastrophe != ECatastrophes::None)
        {
            mm.pushCastastrophe(catastrophe);
        }
        else
        {
            std::cerr 
            << "Can't create a catastrophe o type '" << catastropheName << "'\n";
        }
    }

    std::cout << std::flush;
}
