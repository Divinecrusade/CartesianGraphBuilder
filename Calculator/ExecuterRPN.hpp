#pragma once

#include "IExprExecuter.hpp"
#include <stack>

namespace Calculator
{
    class ExecuterRPN : public MathExpression::IExprExecuter<MathExpression::Notation::RPN>
    {
    public:

        explicit ExecuterRPN(char del = ' ');
        ExecuterRPN(ExecuterRPN const&) = delete;
        ExecuterRPN(ExecuterRPN&&) = delete;

        ExecuterRPN& operator=(ExecuterRPN const&) = delete;
        ExecuterRPN& operator=(ExecuterRPN&&) = delete;

        virtual double execute_expr_according_notation(std::queue<std::string> const& expr) const override;

    private:

        char const DELIMETER;
    };
}