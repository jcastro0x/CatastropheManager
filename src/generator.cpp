#include <common.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

class Command
{
public:
    explicit Command(const std::string& name, std::function<void()> callback)
    : m_name(name), m_callback(callback)
    {
    }

    bool execute(const std::string& input) const
    {
        if(input == m_name)
        {
            m_callback();
            return true;
        }

        return false;
    }

private:
    std::string m_name;
    std::function<void()> m_callback;
};


int main(int argc, char** argv)
{
    std::vector<Command> commands = {

        Command("q", [](){
            std::cout << "Close program\n";
            std::exit(0);
        }),
        Command("execute", [](){
            std::cout << "Close program\n";
            std::exit(0);
        })
    };

    std::cout << "Creating Memory Manager...\n";
    {
        MemoryManager mm;

        std::string line;
        while(std::getline(std::cin, line))
        {
            std::transform(line.begin(), line.end(), line.begin(), std::towlower);
            std::cout << "Input: " << line << "\n";

            for(auto& cmd : commands)
            {
                if(cmd.execute(line)) break;
            }

        }
    }
    std::cout << "Finish..." << std::endl;

    return EXIT_SUCCESS;
}