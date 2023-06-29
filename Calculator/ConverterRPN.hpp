#pragma once

#include <stack>
#include <map>
#include "IConverterRPN.hpp"
#include "Operator.hpp"


class ConverterRPN : IConverterRPN
{
public:

    ConverterRPN() = default;
    ConverterRPN(ConverterRPN const&) = delete;
    ConverterRPN(ConverterRPN&&) = delete;

    ConverterRPN& operator=(ConverterRPN const&) = delete;
    ConverterRPN& operator=(ConverterRPN&&) = delete;

    virtual std::string convert_expr_to_RPN(std::string_view expr) const override;

private:

    std::stack<Operator> operators{ };
    static std::map<Operator, int> const precedences;
    static std::map<Operator, Associativity> const associativities;
};