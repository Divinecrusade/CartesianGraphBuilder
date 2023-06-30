#pragma once

#include "..\Calculator\Operator.hpp"
#include <string>
#include <utility>

namespace GUIApplication
{
    static struct Validater
    {        
       static std::pair<size_t, char const* const> const calculator_symbols;
       static std::pair<size_t, char const* const> const preprocessor_symbols;

       static bool validate(std::string const& expr)
       {
            if (expr.length() == 0) return true;

            enum TokenType
            {
                nan, number, math_operator, preprocessor
            };

            TokenType prev_char{ nan };
            bool prev_char_is_parenthesis{ false };

            for (char const c : expr)
            {
                bool calculator_symbol{ false };
                bool preprocessor_symbol{ false };
                for (size_t i{ 0 }; i != calculator_symbols.first; ++i)
                {
                    if (c == calculator_symbols.second[i])
                    {
                        calculator_symbol = true;
                        break;
                    }
                }
                if (!calculator_symbol)
                {
                    for (size_t i{ 0 }; i != preprocessor_symbols.first; ++i)
                    {
                        if (c == preprocessor_symbols.second[i])
                        {
                            preprocessor_symbol = true;
                            break;
                        }
                    }

                    if (!preprocessor_symbol)
                    {
                        return false;
                    }
                }


                TokenType cur_char{ nan };
                if (preprocessor_symbol)
                {
                    cur_char = preprocessor;
                }
                else if (c >= '0' && c <= '9')
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

                        case preprocessor:

                            return false;

                            break;

                        default:
                            break;
                    }

                    break;

                case math_operator:

                    switch (static_cast<MathExpression::Operator>(c))
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

                            case preprocessor:

                                //return true;
                                
                                break;
                            }

                        break;


                        case MathExpression::Operator::left_parenthesis:

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

                            case preprocessor:

                                return false;

                                break;
                            }

                        break;

                        case MathExpression::Operator::right_parenthesis:
                            
                            switch (prev_char)
                            {
                            case nan:
                                
                                //return true;

                                break;

                            case number:

                                //return true;

                                break;

                            case math_operator:

                                return false;

                                break;

                            case preprocessor:
                                
                                return true;

                                break;
                            }

                        break;

                        default:

                            if (prev_char != number) return false;
                    }

                    break;

                case preprocessor:

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

                    case preprocessor:

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