#pragma once

#include <string>

__interface IConverterRPN
{
    virtual std::string convert_expr_to_RPN(std::string_view expr) const = 0;
};