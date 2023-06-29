#pragma once

#include "..\Calculator\Calculator.hpp"

namespace GUIApplication
{
    static struct Validater
    {        
       static constexpr char available_symbols[] { 'x', 'e' };

       static bool validate(std::string const& expr)
       {
            if (expr.length() == 0) return true;

            enum TokenType
            {
                nan, number, math_operator, special
            };

            TokenType prev_char{ nan };
            bool prev_char_is_parenthesis{ false };

            for (char const c1 : expr)
            {
                bool calculator_symbol{ false };
                bool special_symbol{ false };
                for (char const c2 : MathExprCalculator::Calculator<MathExpression::Notation::RPN>::available_symbols)
                {
                    if (c1 == c2)
                    {
                        calculator_symbol = true;
                        break;
                    }
                }
                if (!calculator_symbol)
                {
                    for (char const c2 : available_symbols)
                    {
                        if (c1 == c2)
                        {
                            special_symbol = true;
                            break;
                        }
                    }

                    if (!special_symbol)
                    {
                        return false;
                    }
                }


                TokenType cur_char{ nan };
                if (special_symbol)
                {
                    cur_char = special;
                }
                else if (c1 >= '0' && c1 <= '9')
                {
                    cur_char = number;
                }
                else
                {
                    cur_char = math_operator;
                }

                switch (cur_char)
                {
                case number:
                    switch (prev_char)
                    {
                        case nan:
                        case number:
                        case math_operator:

                            //return true;

                            break;

                        case special:

                            return false;

                            break;

                        default:
                            break;
                    }

                    break;

                case math_operator:

                    switch (static_cast<MathExpression::Operator>(c1))
                    {
                        case MathExpression::Operator::pow:
                        case MathExpression::Operator::mul:
                        case MathExpression::Operator::div:
                        case MathExpression::Operator::plus:
                        case MathExpression::Operator::minus:

                            switch (prev_char)
                            {
                            case nan:
                                
                                return false;

                                break;

                            case number:
                                
                                //return true;
                                
                                break;

                            case math_operator:

                                if (!prev_char_is_parenthesis) return false;
                                //else return true;

                                break;

                            case special:

                                //return true;
                                
                                break;
                            }

                        break;


                        case MathExpression::Operator::left_parenthesis:
                        case MathExpression::Operator::right_parenthesis:
                            
                            switch (prev_char)
                            {
                            case nan:
                                
                                //return true;

                                break;

                            case number:

                                return false;

                                break;

                            case math_operator:

                                //return true;

                                break;

                            case special:
                                
                                return false;

                                break;
                            }

                        break;

                        default:

                            if (prev_char != number) return false;
                    }

                    break;

                case special:

                    switch (prev_char)
                    {
                    case nan:
                        
                        //return true;

                        break;

                    case number:

                        return false;

                        break;

                    case math_operator:

                        //return true;

                        break;

                    case special:

                        return false;

                        break;
                    }

                    break;
                }

                prev_char = cur_char;
            }

            return true;
       };
    };
}