#include "command.h"
#include <exception>

Command::Command(const std::string& name, std::function<void()> callback)
: Command({name}, "", callback)
{
}

Command::Command(const std::vector<std::string>& names, const std::string& description, std::function<void()> callback)
: m_names(names), m_description(description), m_callback(callback)
{
    if(m_names.size() == 0) throw std::exception("Command with 0 names");
    if(m_callback == false) throw std::exception("Command without bind command");
}

bool Command::execute(const std::string& input) const
{
    if(checkName(input))
    {
        m_callback();
        return true;
    }

    return false;
}

std::string Command::getName() const 
{
    return m_names[0];
}

bool Command::checkName(const std::string& name) const 
{
    for(auto& n : m_names) 
       if(n == name) return true;

    return false;
}