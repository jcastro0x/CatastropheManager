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

#include <commands/command.h>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

Command::Command(ArgsVector names, const std::string& description)
: Command(names, description, "\nN/A")
{
}

Command::Command(ArgsVector names, const std::string& description, const std::string& howtouse)
: m_names(names), m_description(description), m_how_to_use(howtouse)
{
    if(m_names.size() == 0) throw std::runtime_error("Command with 0 names");
}

bool Command::check(Interpreter& interpreter, const std::string& input) const
{
    if(input.empty()) return false;

    auto args = split(input);
    if(checkName(args[0]))
    {
        args.erase(args.begin());
        execute(interpreter, args);
        return true;
    }

    return false;
}

const std::string& Command::getName() const 
{
    return m_names[0];
}

const std::vector<std::string>& Command::getNames() const
{
    return m_names;
}

const std::string& Command::getDescription() const 
{
    return m_description;
}

const std::string& Command::getHowToUse() const
{
    return m_how_to_use;
}

std::vector<std::string> Command::split(const std::string& input) const
{
    std::vector<std::string> result;
    boost::split(result, input, boost::is_any_of(" "));
    return result;  //RVO
}

bool Command::checkName(const std::string& name) const 
{
    for(auto& n : m_names) 
       if(n == name) return true;

    return false;
}