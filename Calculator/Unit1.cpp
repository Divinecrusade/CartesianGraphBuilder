#include "ConverterRPN.hpp"
#include "ExecuterRPN.hpp"
#include "Calculator.hpp"

#include <Windows.h>
#include <iostream>
#include <memory>


int main()
{
    //MathExprCalculator::ConverterRPN converter{ };
    //MathExprCalculator::ExecuterRPN executer{ };
    
    //std::string expr{ "5^2+4*2/(2-5)" };
    //std::string expr{ "1000--7" };
    //std::string expr{ "3" };
    //std::string expr{ "-3" };
    //std::string expr{ "-3+4*2/(1-5)" };
    std::string expr{ "3+4*2/(-1-5)^2" };
    //std::string expr{ "( 1 + 2 ) * 4 + 3 " };

    //std::cin >> std::noskipws >> expr;

    MathExprCalculator::Calculator<MathExpression::Notation::RPN> calculator{ std::make_shared<MathExprCalculator::ConverterRPN>(), std::make_shared<MathExprCalculator::ExecuterRPN>() };

    //auto rpn_expr{ converter.convert_expr_with_notation(expr) };
    //while (!rpn_expr.empty())
    //{
    //    std::cout << rpn_expr.front() << ' ';
    //    rpn_expr.pop();
    //}

    //auto res{ executer.execute_expr_according_notation(rpn_expr) };

    std::cout << calculator.calculate(expr);

    //std::cout << res;

    return EXIT_SUCCESS;
}