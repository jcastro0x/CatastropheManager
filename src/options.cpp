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

#include <options.h>

#include <iostream>
#include <boost/program_options.hpp>


Options::Options(int argc, char** argv)
{
    std::string str_runAs;

    namespace po = boost::program_options;
    po::options_description generic("Options");
    generic.add_options()
    ("help,h",                         "produce help message")
    ("verbose,v",                      "print to stdout all kind of operations")
    
    ("automatic,a",                    "generate automatic catastrophes")    
    ("automatic-rate,r", po::value<float>(&m_automatic_rate)->default_value(10.0f)
    , "seconds rate to generate automatic catastrophes")
    
    ("mode,m",       po::value<std::string>(&str_runAs)->default_value("generator"),
    "run as 'generator' or 'solver'")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, generic), vm);
    po::notify(vm);    

    if (vm.count("help")) 
    {
        std::cout << generic << "\n";
        m_requestExit = true;
        return;
    }

    if(vm.count("verbose"))
    {
        m_verbose = true;
    }

    if(vm.count("automatic"))
    {
        m_automatic = true;
    }

    if (vm.count("automatic-rate")) 
    {
        m_automatic_rate = vm["automatic-rate"].as<float>();
    } 

    if (vm.count("mode")) 
    {
        str_runAs = vm["mode"].as<std::string>();
        std::cout << "Detected mode: " << str_runAs << std::endl;
        std::transform(str_runAs.begin(), str_runAs.end(), str_runAs.begin(), std::towlower);

        if(str_runAs == "solver") m_runAs = EMode::Solver;
        else                      m_runAs = EMode::Generator;
    }

    print_status(); 
}

bool Options::is_verbose() const
{
    return m_verbose;
}
bool Options::is_automatic() const
{
    return m_automatic;
}
float Options::get_automatic_rate() const
{
    return m_automatic_rate;
}

bool Options::is_request_exit() const
{
    return m_requestExit;
}

EMode Options::get_runAs() const
{
    return m_runAs;
}

//TODO: Delete me
void Options::print_status() const 
{
    auto BoolToString = [](bool b) constexpr {
        return b ? "True" : "False";
    };

    std::cout << "Program initialized with next parameters:\n";
    std::cout << "Verbose?       : " << BoolToString(is_verbose())   << "\n";
    std::cout << "Automatic?     : " << BoolToString(is_automatic()) << "\n";
    std::cout << "Automatic Rate : " << get_automatic_rate()         << "\n";
}