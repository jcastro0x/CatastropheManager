#pragma once

#include <string>
#include <vector>
#include <functional>


class Command
{
public:
    explicit Command(const std::string& name, std::function<void()> callback);
    explicit Command(const std::vector<std::string>& names, const std::string& description, std::function<void()> callback);

    bool execute(const std::string& input) const;
    std::string getName() const;

private:
    bool checkName(const std::string& name) const;

private:
    std::vector<std::string> m_names;
    std::string              m_description;
    std::function<void()>    m_callback;
};