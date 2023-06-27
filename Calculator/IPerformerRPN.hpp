#pragma once

#include <string_view>

__interface IPerformerRPN
{
    virtual double calculate(std::string_view RPN_expr) const = 0;
};