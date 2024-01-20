#pragma once

#include <string>
#include <map>

namespace GUIApplication
{
    template<char argument = 'x'>
    class PreCalculator
    {
    private:

        enum Constants : char
        {
            exponent = 'e'
        };

    public:
    
        static constexpr char available_symbols[2] { argument, static_cast<char>(exponent) };

        static std::string process_symbols(std::string_view expr, double arg_value)
        {
            static std::map<Constants, std::string> const constants_values{ {exponent, "2.718"} };

            bool const arg_negative{ arg_value < 0 };

            std::string const arg_value_str{ std::to_string(arg_value) };
            std::string processed_expr{ };

            for (char const c : expr)
            {
                switch (c)
                {
                    case argument:
                        if (arg_negative && processed_expr.length() >= 1 && processed_expr[processed_expr.length() - 1] == '-')
                        {
                            if (processed_expr.length() >= 2 && processed_expr[processed_expr.length() - 2] >= '0' && processed_expr[processed_expr.length() - 2] <= '9')
                            {
                                processed_expr[processed_expr.length() - 1] = '+';
                                processed_expr += std::to_string(-arg_value);
                            }
                            else
                            {
                                processed_expr.erase(processed_expr.length() - 1, 1);
                                processed_expr += std::to_string(-arg_value);
                            }
                        }
                        else
                        {
                            processed_expr += arg_value_str; 
                        }
                        break;
                    case exponent: processed_expr += constants_values.at(exponent); break;
                    default:
                      processed_expr += c;
                }
            }

            return processed_expr;
        }
    };
}