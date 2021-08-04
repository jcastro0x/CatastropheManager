#pragma once

#include <string>
#include <vector>
#include <functional>

class Command
{
public:
    explicit Command(const std::vector<std::string>& names, const std::string& description);
    [[nodiscard]] bool check(class Interpreter& interpreter, const std::string& input) const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getDescription() const;

protected:
    virtual void execute(class Interpreter& interpreter, std::vector<std::string>& args) const = 0;

private:
    [[nodiscard]] std::vector<std::string> split(const std::string& input) const;
    [[nodiscard]] bool checkName(const std::string& name) const;

private:
    std::vector<std::string> m_names;
    std::string              m_description;
};