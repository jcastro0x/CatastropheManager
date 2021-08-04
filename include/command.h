#pragma once

#include <string>
#include <vector>
#include <functional>


class Command
{
    typedef std::function<void(class Interpreter&, std::vector<std::string>&)> CmdCallback;

public:
    explicit Command(const std::string& name, CmdCallback callback);
    explicit Command(const std::vector<std::string>& names, const std::string& description, CmdCallback callback);

    bool execute(class Interpreter& interpreter, const std::string& input) const;
    std::string getName() const;

private:
    std::vector<std::string> split(const std::string& input) const;
    bool checkName(const std::string& name) const;

private:
    std::vector<std::string> m_names;
    std::string              m_description;
    CmdCallback              m_callback;
};