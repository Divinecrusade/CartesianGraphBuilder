#pragma once

#include "ICalculator.hpp"
#include "Notation.hpp"
#include "IExprConverter.hpp"
#include "IExprExecuter.hpp"
#include "Operator.hpp"

#include <memory>
#include <cassert>
#include <iterator>

namespace MathExprCalculator
{
    template<MathExpression::Notation N>
    class Calculator : public ICalculator
    {
    public:

        Calculator(std::shared_ptr<MathExpression::IExprConverter<N>> const& expr_converter, std::shared_ptr<MathExpression::IExprExecuter<N>> const& expr_executer)
        :
        converter{ expr_converter },
        executer { expr_executer }
        { }
        
        Calculator(Calculator const&) = delete;
        Calculator(Calculator &&) = delete;

        Calculator& operator=(Calculator const&) = delete;
        Calculator& operator=(Calculator&&) = delete;

        ~Calculator() = default;

        virtual double calculate(std::string_view expr) const override
        {
            char const delimeter{ converter->get_delimeter() };
            bool prev_char_is_operator{ false };

            std::string formatted_expr{ };
            for (size_t i{ 0 }; i != expr.length(); ++i)
            {
                if (is_digit(expr[i]) || expr[i] == '.' ||
                   (expr[i] == '-' && 
                   (i == 0 || 
                   (is_digit(expr[i + 1]) && !is_digit(expr[i - 1])))))
                {
                    if (prev_char_is_operator)
                    {
                        formatted_expr += delimeter;
                    }

                    formatted_expr += expr[i];
                    prev_char_is_operator = false;
                }
                else
                {
                    formatted_expr += delimeter;
                    formatted_expr += expr[i];

                    prev_char_is_operator = true;
                }
            }
            formatted_expr += delimeter;


            return executer->execute_expr_according_notation(converter->convert_expr_with_notation(formatted_expr));
        }

        static constexpr char available_symbols[] { 
        static_cast<char>(MathExpression::Operator::pow), 
        static_cast<char>(MathExpression::Operator::mul),  static_cast<char>(MathExpression::Operator::div),
        static_cast<char>(MathExpression::Operator::plus), static_cast<char>(MathExpression::Operator::minus),
        static_cast<char>(MathExpression::Operator::left_parenthesis), static_cast<char>(MathExpression::Operator::right_parenthesis),
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0', '.'
        };

    private:

        bool is_digit(char c) const
        {
            return c >= '0' && c <= '9';
        }

        std::shared_ptr< MathExpression::IExprConverter<N> > converter;
        std::shared_ptr< MathExpression::IExprExecuter<N> >  executer;
    };
}