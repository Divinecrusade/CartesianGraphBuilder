#pragma once

#include "Notation.hpp"

#include <queue>
#include <string>

namespace MathExpression
{
    template<Notation>
    __interface IExprConverter
    {
    public:

        virtual std::queue<std::string> convert_expr_with_notation(std::string_view expr) const = 0;
    };
}