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
            static std::map<Constants, std::string> const constants_value{ {exponent, "2.718"} };

            std::ostringstream sout{ };
            sout << arg_value;
            std::string arg_value_str{ sout.str() };
            std::string processed_expr{ };

            for (auto const& c : expr)
            {
                switch (c)
                {
                    case argument: processed_expr += arg_value_str; break;
                    case exponent: processed_expr += constants_value[exponent]; break;
                    default: processed_expr += c;
                }
            }

            return processed_expr;
        }
    };
}