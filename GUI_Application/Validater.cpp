#include "Validater.hpp"


namespace GUIApplication
{
    Validater::TokenType Validater::check_char(wchar_t c)
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
            for (size_t i{ 0 }; i != precalculator_symbols.first; ++i)
            {
                if (c == precalculator_symbols.second[i])
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
            return precalculator;
        }
        else if (c >= L'0' && c <= L'9')
        {
            return number;
        }
        else
        {
            return math_operator;
        }
    }

    bool Validater::validate(std::string const& expr)
    {
        if (expr.length() == 0) return true;

        TokenType prev_char{ nan };
        bool prev_char_is_left_parenthesis{ false };
        bool prev_char_is_right_parenthesis{ false };
        int parenthesis_balance{ 0 };

        for (size_t i{ 0 }; i != expr.length(); ++i)
        {
            char const c{ expr[i] };
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

                case precalculator:

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

                    case precalculator:

                        //return true;

                        break;
                    }

                    prev_char_is_left_parenthesis = prev_char_is_right_parenthesis = false;

                    break;

                case MathExpression::Operator::minus:

                    switch (prev_char)
                    {
                    case nan:

                        break;

                    case number:

                        //return true;

                        break;

                    case math_operator:

                        if (expr[i - 1] == '-' || expr[i - 1] == '+') return false;
                        else if (!(prev_char_is_right_parenthesis ||
                              (i + 1 != expr.length() &&
                              (check_char(expr[i + 1]) == number ||
                               check_char(expr[i + 1]) == precalculator)))) return false;
                        //else return true;

                        break;

                    case precalculator:

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

                    case precalculator:

                        return false;

                        break;
                    }

                    ++parenthesis_balance;
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

                        if (!prev_char_is_right_parenthesis) return false;

                        break;

                    case precalculator:

                        return true;

                        break;
                    }

                    --parenthesis_balance;
                    prev_char_is_left_parenthesis = false;
                    prev_char_is_right_parenthesis = true;

                    break;
                }

                break;

            case precalculator:

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

                case precalculator:

                    return false;

                    break;
                }

                prev_char_is_left_parenthesis = prev_char_is_right_parenthesis = false;

                break;
            }

            prev_char = cur_char;
        }

        if (parenthesis_balance != 0) return false;

        return true;
    }

    bool Validater::validate(wchar_t key_code)
    {
        if (key_code >= '!' && key_code <= '~')
        {
            if (check_char(key_code) == invalid) return false;
            else return true;
        }
        else return true;
    }
}