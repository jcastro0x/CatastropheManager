#include <commands/command.h>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

Command::Command(const std::vector<std::string>& names, const std::string& description)
: m_names(names), m_description(description)
{
    if(m_names.size() == 0) throw std::runtime_error("Command with 0 names");
}

bool Command::check(class Interpreter& interpreter, const std::string& input) const
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

const std::string& Command::getDescription() const 
{
    return m_description;
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