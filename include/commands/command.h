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

#pragma once

#include <string>
#include <vector>
#include <functional>

typedef const std::vector<std::string>& ArgsVector;

class Command
{
public:
    explicit Command(ArgsVector names, const std::string& description);
    explicit Command(ArgsVector names, const std::string& description, const std::string& howtouse);

    virtual ~Command() = default;

    [[nodiscard]] bool check(class Interpreter& interpreter, const std::string& input) const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::vector<std::string>& getNames() const;
    [[nodiscard]] const std::string& getDescription() const;
    [[nodiscard]] const std::string& getHowToUse() const;

protected:
    virtual void execute(class Interpreter& interpreter, ArgsVector args) const = 0;

private:
    [[nodiscard]] std::vector<std::string> split(const std::string& input) const;
    [[nodiscard]] bool checkName(const std::string& name) const;

private:
    std::vector<std::string> m_names;
    std::string              m_description;
    std::string              m_how_to_use;
};