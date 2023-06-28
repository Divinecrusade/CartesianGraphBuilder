#pragma once

#include <string_view>

namespace Calculator
{
    __interface ICalculator
    {
        virtual double calculate(std::string_view expr) const = 0;
    };
}