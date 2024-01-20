#pragma once

#include "Notation.hpp"

#include <string_view>

namespace MathExpression
{
    template<Notation>
    __interface IExprExecuter
    {
        virtual double execute_expr_according_notation(std::string_view expr) const = 0;
    };
}