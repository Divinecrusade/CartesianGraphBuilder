#pragma once

#include <stack>
#include <map>
#include "IExprConverter.hpp"
#include "Notation.hpp"
#include "Operator.hpp"

namespace Calculator
{
    class ConverterRPN : public MathExpression::IExprConverter<MathExpression::Notation::RPN>
    {
    public:

        explicit ConverterRPN(char del = ' ');
        ConverterRPN(ConverterRPN const&) = delete;
        ConverterRPN(ConverterRPN&&) = delete;

        ConverterRPN& operator=(ConverterRPN const&) = delete;
        ConverterRPN& operator=(ConverterRPN&&) = delete;

        virtual std::queue<std::string> convert_expr_with_notation(std::string_view expr) const override;

    private:
        
        char const DELIMETER;

        static bool is_operator(std::string_view token);
        static MathExpression::Operator parse_operator(std::string_view token);
        static std::string to_string(MathExpression::Operator const& o);

        static std::map<MathExpression::Operator const, int const> const precedences;
        static std::map<MathExpression::Operator const, MathExpression::Associativity const> const associativities;
    };
}