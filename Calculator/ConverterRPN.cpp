#include "ConverterRPN.hpp"

std::map<Operator, int> const ConverterRPN::precedences{ {Operator::pow, 4}, { Operator::mul, 3 }, { Operator::div, 3 }, { Operator::plus, 2 }, { Operator::minus, 2 } };
std::map<Operator, Associativity> const ConverterRPN::associativities{ {Operator::pow, Associativity::right}, { Operator::mul, Associativity::left }, { Operator::div, Associativity::left }, { Operator::plus, Associativity::left }, { Operator::minus, Associativity::left } };

std::string ConverterRPN::convert_expr_to_RPN(std::string_view expr) const
{
    return std::string{};
}
