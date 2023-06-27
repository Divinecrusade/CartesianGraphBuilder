#pragma once

enum class Operator : char
{
    pow = '^',
    plus = '+',
    minus = '-',
    mul = '*',
    div = '/'
};

enum class Associativity
{
    left, right
};