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

#include <options.h>
#include <memory>
#include <iostream>

struct Log
{
    static void initialize(std::shared_ptr<const Options> options) noexcept
    {
        m_options = options;
    }

    static void cls() noexcept
    {
        std::cout << "\033[2J"; // clear screen
    }

    static void print(const char* format) noexcept
    {
        std::cout << format << '\n';
    }

    static void log(const char* format)
    {
        if(m_options->is_verbose())
        {
            std::cout << format << '\n';
        }
    }

    static void war(const char* format)
    {
        if(m_options->is_verbose())
        {
            std::cout << "\033[33m";        // yellow
            std::cout << format << '\n';
            std::cout << "\033[0m";
        }
    }

    static void err(const char* format) noexcept
    {
        // We want to print errors even if --verbose flag aren't set
        std::cout << "\033[31m";        // red
        std::cerr << format << '\n';
        std::cout << "\033[0m";
    }

    static void flush() noexcept
    {
        std::cout << std::flush;
    }

private:
    inline static std::shared_ptr<const Options> m_options { nullptr };
};
