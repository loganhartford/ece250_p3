#ifndef ILLEGAL_EXCEPTION_HPP
#define ILLEGAL_EXCEPTION_HPP

#include <exception>
#include <string>
using namespace std;

class illegal_exception : public exception
{
public:
    const char *what() const noexcept override
    {
        return "illegal argument";
    }
};

#endif
