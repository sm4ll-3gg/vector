#ifndef VEXCEPTION_H
#define VEXCEPTION_H

#include <exception>
#include <string>

class VException : public std::exception
{
    std::string name;
public:
    VException();
    VException(const std::string&);
    VException(const std::string&, std::exception&);

    const std::string& get_name() const;
};

#endif // VEXCEPTION_H
