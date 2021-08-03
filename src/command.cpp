#include "command.h"
#include <stdexcept>

#include <boost/algorithm/string.hpp>

Command::Command(const std::string& name, std::function<void(std::vector<std::string>&)> callback)
: Command({name}, "", callback)
{
}

Command::Command(const std::vector<std::string>& names, const std::string& description, std::function<void(std::vector<std::string>&)> callback)
: m_names(names), m_description(description), m_callback(callback)
{
    if(m_names.size() == 0) throw std::runtime_error("Command with 0 names");
    if(!m_callback)         throw std::runtime_error("Command without bind command");
}

bool Command::execute(const std::string& input) const
{
    if(input.empty()) return false;

    auto args = split(input);
    if(checkName(args[0]))
    {
        args.erase(args.begin());
        m_callback(args);
        return true;
    }

    return false;
}

std::string Command::getName() const 
{
    return m_names[0];
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