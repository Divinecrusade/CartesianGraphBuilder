#pragma once

#include <string_view>

namespace MathExprCalculator
{
    __interface ICalculator
    {
        virtual double calculate(std::string_view expr) const = 0;
    };
}