#include "ConverterRPN.hpp"

#include <vector>
#include <cassert>

namespace MathExprCalculator
{
    std::map<MathExpression::Operator const, int const> const ConverterRPN::precedences{ { MathExpression::Operator::pow, 4 }, { MathExpression::Operator::mul, 3 },
                                                                                         { MathExpression::Operator::div, 3 }, { MathExpression::Operator::plus, 2 }, 
                                                                                         { MathExpression::Operator::minus, 2 } };
    std::map<MathExpression::Operator const, MathExpression::Associativity const> const ConverterRPN::associativities{ { MathExpression::Operator::pow, MathExpression::Associativity::right }, { MathExpression::Operator::mul, MathExpression::Associativity::left },
                                                                                                                       { MathExpression::Operator::div, MathExpression::Associativity::left }, { MathExpression::Operator::plus, MathExpression::Associativity::left },
                                                                                                                       { MathExpression::Operator::minus, MathExpression::Associativity::left } };

    ConverterRPN::ConverterRPN(char del) : DELIMETER{ del } { }

    std::queue<std::string> ConverterRPN::convert_expr_with_notation(std::string_view expr) const
    {
        std::stack<MathExpression::Operator> operators{ };
        std::queue<std::string> result{ };
    
        std::vector<std::string> tokens{ };
        size_t last_space_pos{ 0 };
        size_t space_pos{ expr.find(DELIMETER, last_space_pos) };
    
        while (space_pos != std::string::npos)
        {
            tokens.push_back(std::string{ expr.substr(last_space_pos, space_pos - last_space_pos) });
            last_space_pos = space_pos + 1;
            space_pos = expr.find(DELIMETER, last_space_pos);
        }

        for (auto const& token : tokens)
        {
            if (is_operator(token))
            {
                auto const o1{ parse_operator(token) };
                switch (o1)
                {
                    case MathExpression::Operator::left_parenthesis: 
                    {
                        operators.push(o1); 
                    }

                    break;

                    case MathExpression::Operator::right_parenthesis: 
                    {
                        while (operators.top() != MathExpression::Operator::left_parenthesis)
                        {
                            assert(!operators.empty());

                            auto const& o2{ operators.top() };
                            result.push(to_string(o2));

                            operators.pop();
                        }

                        assert(operators.top() == MathExpression::Operator::left_parenthesis);

                        operators.pop();
                    }

                    break;

                    default:
                    {
                        while ( (!operators.empty() && operators.top() != MathExpression::Operator::left_parenthesis) &&
                                (precedences.at(operators.top()) > precedences.at(o1) ||
                                (precedences.at(operators.top()) == precedences.at(o1) && associativities.at(o1) == MathExpression::Associativity::left)) )
                        {
                            auto const& o2{ operators.top() };
                            result.push(to_string(o2));

                            operators.pop();                            
                        }

                        operators.push(o1);
                    }

                    break;
                }
            }
            else
            {
                result.push(std::string{ token });
            }
        }
        
        while (!operators.empty())
        {
            auto const& o{ operators.top() };

            assert(o != MathExpression::Operator::left_parenthesis);

            result.push(to_string(o));

            operators.pop();
        }

        return result;
    }

    bool ConverterRPN::is_operator(std::string_view token)
    {
        if (token.length() > 1 || (token[0] >= '0' && token[0] <= '9')) return false;
        else return true;
    }

    MathExpression::Operator ConverterRPN::parse_operator(std::string_view token)
    {
        assert(is_operator(token));

        return static_cast<MathExpression::Operator>(token[0]);
    }

    std::string ConverterRPN::to_string(MathExpression::Operator const& o)
    {
        return std::string{ static_cast<char>(o) };
    }
}
