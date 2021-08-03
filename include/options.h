#pragma once

class options
{
public:
    explicit options(int argc, char** argv);

public:
    bool is_verbose() const; 
    bool is_automatic() const;
    float get_automatic_rate() const;

    bool is_request_exit() const;

public:
    void print_status() const;

private:
    bool m_verbose              { false };
    bool m_automatic            { false };
    float m_automatic_rate      { 10.f  };

    bool m_requestExit          { false };
};