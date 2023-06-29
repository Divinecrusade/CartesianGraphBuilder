#include "ExecuterRPN.hpp"
#include "Operator.hpp"

#include <sstream>
#include <exception>
#include <cassert>
#include <cmath>

namespace MathExprCalculator
{
    double ExecuterRPN::execute_expr_according_notation(std::queue<std::string> const& expr) const
    {
        static constexpr char DELIMETER{ ' ' };
        std::stack<double> operands{ };
        std::string expr_line{  };

        for (auto const& token : expr._Get_container())
        {
            expr_line += token;
            expr_line += DELIMETER;
        }
        // !!!
        expr_line.erase(expr_line.length() - 1, expr_line.length() - 1);

        std::istringstream ssin{expr_line};
        ssin.exceptions(std::ios::failbit);

        while (ssin.peek() != EOF)
        {
            double x{ };
            MathExpression::Operator o{ };
            auto g{ ssin.tellg() };

            try
            {
                ssin >> x;

                operands.push(x);
            }
            catch (std::ios_base::failure const&)
            {
                char c{ };
                ssin.clear();
                ssin.seekg(g);
                ssin >> c;

                o = static_cast<MathExpression::Operator>(c);

                double operation_result{ };

                switch (o)
                {
                    case MathExpression::Operator::div:
                    {
                        assert(operands.size() > 1);

                        double const b{ operands.top() };
                        operands.pop();

                        double const a{ operands.top() };
                        operands.pop();

                        operation_result = a / b;
                    }

                    break;

                    case MathExpression::Operator::mul:
                    {
                        assert(operands.size() > 1);

                        double const b{ operands.top() };
                        operands.pop();

                        double const a{ operands.top() };
                        operands.pop();

                        operation_result = a * b;
                    }

                    break;

                    case MathExpression::Operator::minus:
                    {
                        assert(operands.size() > 1);

                        double const b{ operands.top() };
                        operands.pop();

                        double const a{ operands.top() };
                        operands.pop();

                        operation_result = a - b;
                    }

                    break;

                    case MathExpression::Operator::plus:
                    {
                        assert(operands.size() > 1);

                        double const b{ operands.top() };
                        operands.pop();

                        double const a{ operands.top() };
                        operands.pop();

                        operation_result = a + b;
                    }

                    break;

                    case MathExpression::Operator::pow:
                    {
                        assert(operands.size() > 1);

                        double const b{ operands.top() };
                        operands.pop();

                        double const a{ operands.top() };
                        operands.pop();

                        operation_result = std::pow(a, b);
                    }

                    break;

                    //default:

                        //throw std::exception{ "Bad RPN notation expression" };
                }

                operands.push(operation_result);
            }
        }

        assert(operands.size() == 1);

        double const result{ operands.top() };
        operands.pop();

        return result;
    }
}


