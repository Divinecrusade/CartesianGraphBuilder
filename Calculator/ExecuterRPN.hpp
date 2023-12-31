#pragma once

#include "IExprExecuter.hpp"
#include <stack>

namespace MathExprCalculator
{
    class ExecuterRPN : public MathExpression::IExprExecuter<MathExpression::Notation::RPN>
    {
    public:

        ExecuterRPN() = default;
        ExecuterRPN(ExecuterRPN const&) = delete;
        ExecuterRPN(ExecuterRPN&&) = delete;

        ExecuterRPN& operator=(ExecuterRPN const&) = delete;
        ExecuterRPN& operator=(ExecuterRPN&&) = delete;

        virtual ~ExecuterRPN() = default;

        virtual double execute_expr_according_notation(std::queue<std::string> const& expr) const override;
    };
}