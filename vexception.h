#ifndef VEXCEPTION_H
#define VEXCEPTION_H

#include <exception>
#include <string>

class VException : public std::exception
{
    std::string name;
public:
    VException();
    VException(std::string);
    VException(std::string, std::exception&);

    std::string get_name() const;
};

#endif // VEXCEPTION_H
