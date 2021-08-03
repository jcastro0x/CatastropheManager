#include "options.h"

#include <iostream>
#include <boost/program_options.hpp>


options::options(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description generic("Options");
    generic.add_options()
    ("help,h",                                "produce help message")
    ("verbose,v",                             "print to stdout all kind of operations")
    ("automatic,a",                           "generate automatic catastrophes")
    ("automatic-rate,r",  po::value<float>(&m_automatic_rate)->default_value(10.0f)
    , "seconds rate to generate automatic catastrophes")
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

    if(vm.count("automatic"))
    {
        m_automatic = true;
    }

    if (vm.count("automatic-rate")) 
    {
        m_automatic_rate = vm["automatic-rate"].as<float>();
    } 
}

bool options::is_verbose() const
{
    return m_verbose;
}
bool options::is_automatic() const
{
    return m_automatic;
}
float options::get_automatic_rate() const
{
    return m_automatic_rate;
}

bool options::is_request_exit() const
{
    return m_requestExit;
}


void options::print_status() const 
{
    auto BoolToString = [](bool b) constexpr {
        return b ? "True" : "False";
    };

    std::cout << "Program initialized with next parameters:\n";
    std::cout << "Verbose?       : " << BoolToString(is_verbose())   << "\n";
    std::cout << "Automatic?     : " << BoolToString(is_automatic()) << "\n";
    std::cout << "Automatic Rate : " << get_automatic_rate()         << "\n";
}