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

#include <cstdint>

enum class EMode : uint8_t
{
    Generator,
    Solver
};

class Options
{
public:
    explicit Options(int argc, char** argv);

public:
    [[nodiscard]] bool is_verbose() const; 
    [[nodiscard]] bool is_automatic() const;
    [[nodiscard]] bool is_no_clear() const;
    [[nodiscard]] bool is_request_exit() const;
    [[nodiscard]] float get_automatic_rate() const;
    [[nodiscard]] EMode get_runAs() const;

private:
    bool m_verbose              { false };
    bool m_automatic            { false };
    bool m_no_clear             { false };
    
    float m_automatic_rate      { 10.f  };

    bool m_requestExit          { false };

    EMode m_runAs               { EMode::Generator };
};