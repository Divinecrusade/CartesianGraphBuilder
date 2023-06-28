#pragma once

#include "Notation.hpp"

#include <string>
#include <queue>

namespace MathExpression
{
    template<Notation>
    __interface IExprExecuter
    {
        virtual double execute_expr_according_notation(std::queue<std::string> const& expr) const = 0;
    };
}