#include "vexception.h"

VException::VException()
    :name("No problems") {}

VException::VException(const std::string& _name)
    :name(_name) {}

VException::VException(const std::string& _name, std::exception& ex)
    :std::exception(ex), name(_name) {}

const std::string& VException::get_name() const
{
    return name;
}
