#pragma once

#include "ICalculator.hpp"
#include "Notation.hpp"
#include "IExprConverter.hpp"
#include "IExprExecuter.hpp"
#include "Operator.hpp"

#include <memory>

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

        virtual double calculate(std::string_view expr) const override
        {
            /*assert(bool[expr, &available_symbols]() = > {
                for (char const& c1 : expr)
                {
                    bool correct_symbol{ false };

                    for (char const& c2 : available_symbols)
                    {
                        if (c1 == c2)
                        {
                            correct_symbol = true;
                            break;
                        }
                    }

                    if (!correct_symbol) return false;
                }

                return true;
            }());*/

            char const delimeter{ converter->get_delimeter() };
            bool prev_char_is_operator{ false };

            std::string formatted_expr{ };
            for (size_t i{ 0 }; i != expr.length(); ++i)
            {
                if ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')
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
        static_cast<char>(MathExpression::Operator::left_parenthesis), static_cast<char>(MathExpression::Operator::right_parenthesis,
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0', '.')
        };

    private:

        std::shared_ptr< MathExpression::IExprConverter<N> > converter;
        std::shared_ptr< MathExpression::IExprExecuter<N> >  executer;
    };
}