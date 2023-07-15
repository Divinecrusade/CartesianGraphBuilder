#pragma once

#include "..\Calculator\Operator.hpp"
#include <string>
#include <utility>

namespace GUIApplication
{
    class Validater
    {        
    private:

       static std::pair<size_t, char const*> const calculator_symbols;
       static std::pair<size_t, char const*> const precalculator_symbols;

       enum TokenType
       {
           nan, invalid, number, math_operator, precalculator
       };

    private:

        static TokenType check_char(wchar_t c);

    public:

       static bool validate(std::string const& expr);
       static bool validate(wchar_t key_code);
    
    };
}