#include "ConverterRPN.hpp"

#include <Windows.h>
#include <iostream>


int main()
{
    Calculator::ConverterRPN converter{ };
    
    std::string expr{ "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3 " };

    //std::cin >> std::noskipws >> expr;

    auto rpn_expr{ converter.convert_expr_with_notation(expr) };
    while (!rpn_expr.empty())
    {
        std::cout << rpn_expr.front() << ' ';
        rpn_expr.pop();
    }


    return EXIT_SUCCESS;
}