#pragma once

#include "..\Calculator\Operator.hpp"
#include <string>
#include <utility>

namespace GUIApplication
{
    static class Validater
    {        
    private:

       static std::pair<size_t const, char const* const> const calculator_symbols;
       static std::pair<size_t const, char const* const> const preprocessor_symbols;

       enum TokenType
       {
           nan, invalid, number, math_operator, preprocessor
       };

    private:

        static TokenType check_char(char c)
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
                    return invalid;
                }
            }

            if (preprocessor_symbol)
            {
                return preprocessor;
            }
            else if (c >= '0' && c <= '9')
            {
                return number;
            }
            else
            {
                return math_operator;
            }
        }

    public:

       static bool validate(std::string const& expr)
       {
            if (expr.length() == 0) return true;

            TokenType prev_char{ nan };
            bool prev_char_is_left_parenthesis{ false };
            bool prev_char_is_right_parenthesis{ false };

            for (char const c : expr)
            {
                TokenType cur_char{ check_char(c) };

                switch (cur_char)
                {
                case invalid:

                    return false;
                    
                    break;

                case number:

                    switch (prev_char)
                    {
                        case nan:
                        case number:
                        case math_operator:

                            if (prev_char_is_right_parenthesis) return false;
                            //return true;

                            break;

                        case preprocessor:

                            return false;

                            break;

                        default:
                            break;
                    }

                    prev_char_is_left_parenthesis = prev_char_is_right_parenthesis = false;

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

                                if (!prev_char_is_right_parenthesis) return false;
                                //else return true;

                                break;

                            case preprocessor:

                                //return true;
                                
                                break;
                            }

                            prev_char_is_left_parenthesis = prev_char_is_right_parenthesis = false;

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

                            prev_char_is_left_parenthesis = true;
                            prev_char_is_right_parenthesis = false;

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

                            prev_char_is_left_parenthesis = false;
                            prev_char_is_right_parenthesis = true;

                        break;
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

                    prev_char_is_left_parenthesis = prev_char_is_right_parenthesis = false;

                    break;
                }

                prev_char = cur_char;
            }

            return true;
       };
       
       static bool validate(int key_code)
       {
           if (key_code >= '!' && key_code <= '~')
           {
               if (check_char(key_code) == invalid) return false;
               else return true;
           }
           else return true;
       };
    
    };
}