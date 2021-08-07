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

#include <commands/catastrophes_list.h>
#include <interpreter.h>
#include <log.h>

#include <boost/format.hpp>
#include <iostream>

CmdCatastrophesList::CmdCatastrophesList()
: Command({"catastrophes-list", "clist"}, "List all available catastrophes")
{
}

void CmdCatastrophesList::execute(Interpreter& interpreter, ArgsVector args) const
{
    const auto& mm = interpreter.getMemoryManager();

    for(int i = 0; i < static_cast<int>(ECatastrophes::COUNT); i++)
    {
        const auto name = mm.getCastastropheName(static_cast<ECatastrophes>(i));
        Log::print( (boost::format("[%1%] %2%") % (i+1) % name).str().c_str() );
    }
    Log::flush();
}
