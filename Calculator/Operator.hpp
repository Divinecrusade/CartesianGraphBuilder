#pragma once

namespace MathExpression
{
    enum class Operator : char
    {
        pow = '^',
        mul = '*',
        div = '/',
        plus = '+',
        minus = '-',
        left_parenthesis = '(',
        right_parenthesis = ')'
    };

    enum class Associativity
    {
        left, right
    };
}