#include <options.h>

#include <iostream>
#include <boost/program_options.hpp>


Options::Options(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description generic("Options");
    generic.add_options()
    ("help,h",                                "produce help message")
    ("verbose,v",                             "print to stdout all kind of operations")
    ("mode,m",                                "run as Generator or Solver")
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

    if (vm.count("mode")) 
    {
        std::string str_mode = vm["mode"].as<std::string>();
        std::transform(str_mode.begin(), str_mode.end(), str_mode.begin(), std::towlower);
        if(str_mode == "solver") m_runAs = EMode::Solver;
        else m_runAs = EMode::Generator;
    } 
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